#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <array>
#include <optional>
#include <cassert>

void thread_atomic_example();

struct myStruct1
{
  int a;
  int b;
};

struct myStruct2
{
  int a;
  int b;
  int c[100];
};

template <typename T, std::size_t N>
class LockFreeStack
{
public:
  LockFreeStack() : top_idx(-1) {}

  bool push(const T &value)
  {
    int old_idx, new_idx;
    do
    {
      old_idx = top_idx.load();
      new_idx = old_idx + 1;
      if (new_idx >= static_cast<int>(N))
      {
        return false; // Stack overflow
      }
    } while (!top_idx.compare_exchange_weak(old_idx, new_idx));

    data[new_idx] = value;
    return true;
  }

  std::optional<T> pop()
  {
    int old_idx, new_idx;
    do
    {
      old_idx = top_idx.load();
      if (old_idx < 0)
      {
        return std::nullopt; // Stack underflow
      }
      new_idx = old_idx - 1;
    } while (!top_idx.compare_exchange_weak(old_idx, new_idx));

    return data[old_idx];
  }

  std::optional<T> get(std::size_t index)
  {
    if (index >= N || index < 0)
    {
      return std::nullopt; // Invalid index
    }
    return data[index];
  }

  void print()
  {
    for (int i = 0; i <= top_idx.load(); ++i)
    {
      std::cout << data[i] << " ";
    }
    std::cout << std::endl;
  }

private:
  std::array<T, N> data;
  std::atomic<int> top_idx;
};
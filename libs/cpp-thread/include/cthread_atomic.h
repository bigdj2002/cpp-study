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

template <typename T, std::size_t Capacity>
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
      if (new_idx >= static_cast<int>(Capacity))
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
    if (index >= Capacity || index < 0)
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
  std::array<T, Capacity> data;
  std::atomic<int> top_idx;
};

template <typename T, std::size_t Capacity>
class LockFreeQueue
{
public:
  LockFreeQueue() : head(0), tail(0) {}

  bool push(const T &value)
  {
    std::size_t currTail = tail.load();
    std::size_t nextTail = (currTail + 1) % Capacity;

    if (nextTail == head.load())
      return false; // Queue is full

    buffer[currTail] = value;
    tail.store(nextTail);
    return true;
  }

  bool pop(T &value)
  {
    std::size_t currHead = head.load();
    if (currHead == tail.load())
      return false; // Queue is empty

    value = buffer[currHead];
    head.store((currHead + 1) % Capacity);
    return true;
  }

  std::optional<T> get(std::size_t index)
  {
    if (index >= Capacity)
      return std::nullopt; // Invalid index

    std::size_t currHead = head.load();
    std::size_t currTail = tail.load();

    if (currHead <= currTail)
    {
      if (index < currTail - currHead)
        return buffer[currHead + index];
    }
    else
    {
      std::size_t wrappedIndex = currHead + index;
      if (wrappedIndex < Capacity)
        return buffer[wrappedIndex];
      wrappedIndex -= Capacity;
      if (wrappedIndex < currTail)
        return buffer[wrappedIndex];
    }

    return std::nullopt; // Index out of range
  }

  void printQueue()
  {
    std::size_t currentHead = head.load(std::memory_order_relaxed);
    std::size_t currentTail = tail.load(std::memory_order_relaxed);
    while (currentHead != currentTail)
    {
      std::cout << buffer[currentHead] << " ";
      currentHead = IncrementIndex(currentHead);
    }
  }

  bool IsEmpty() const
  {
    return head.load() == tail.load();
  }

private:
  std::array<T, Capacity> buffer;
  std::atomic<std::size_t> head;
  std::atomic<std::size_t> tail;

  std::size_t IncrementIndex(std::size_t index) const
  {
    return (index + 1) % Capacity;
  }
};
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
  LockFreeStack() : top_idx(-1) {} // 스택 생성자: 스택 최상단 위치를 -1로 설정합니다.

  bool push(const T &value) // 값을 스택에 푸시합니다.
  {
    int old_idx, new_idx;
    do
    {
      // 현재 top_idx를 가져옵니다.
      old_idx = top_idx.load();
      new_idx = old_idx + 1;

      if (new_idx >= static_cast<int>(Capacity)) // 스택이 가득 찼는지 확인합니다.
      {
        return false; // 스택 오버플로우
      }
    } while (!top_idx.compare_exchange_weak(old_idx, new_idx)); // top_idx를 new_idx로 업데이트하려고 시도합니다.

    // 스택의 새로운 top에 값을 넣습니다.
    data[new_idx] = value;
    return true;
  }

  std::optional<T> pop() // 스택의 최상단 값을 팝합니다.
  {
    int old_idx, new_idx;
    do
    {
      old_idx = top_idx.load();

      if (old_idx < 0) // 스택이 비어 있는지 확인합니다.
      {
        return std::nullopt; // 스택 언더플로우
      }
      new_idx = old_idx - 1;

    } while (!top_idx.compare_exchange_weak(old_idx, new_idx)); // top_idx를 new_idx로 업데이트하려고 시도합니다.

    return data[old_idx]; // 팝할 값을 반환합니다.
  }

  std::optional<T> get(std::size_t index) // 주어진 인덱스의 스택 값을 가져옵니다.
  {
    if (index >= Capacity || index < 0)
    {
      return std::nullopt; // 유효하지 않은 인덱스
    }
    return data[index];
  }

  void print() // 스택의 모든 값을 출력합니다.
  {
    for (int i = 0; i <= top_idx.load(); ++i)
    {
      std::cout << data[i] << " ";
    }
    std::cout << std::endl;
  }

private:
  std::array<T, Capacity> data; // 스택의 데이터를 저장하는 배열입니다.
  std::atomic<int> top_idx;     // 스택의 최상단 위치를 나타내는 원자적 변수입니다.
};

template <typename T, std::size_t Capacity>
class LockFreeQueue
{
public:
  LockFreeQueue() : head(0), tail(0) {} // 큐 생성자: 헤드와 테일을 0으로 설정합니다.

  bool push(const T &value) // 값을 큐에 푸시합니다.
  {
    std::size_t currTail = tail.load();
    std::size_t nextTail = (currTail + 1) % Capacity;

    if (nextTail == head.load()) // 큐가 가득 찼는지 확인합니다.
      return false;              // 큐가 가득 찼습니다.

    buffer[currTail] = value;
    tail.store(nextTail);
    return true;
  }

  bool pop(T &value) // 큐의 가장 앞쪽 값을 팝합니다.
  {
    std::size_t currHead = head.load();
    if (currHead == tail.load()) // 큐가 비어 있는지 확인합니다.
      return false;              // 큐가 비어 있습니다.

    value = buffer[currHead];
    head.store((currHead + 1) % Capacity);
    return true;
  }

  std::optional<T> get(std::size_t index) // 주어진 인덱스의 큐 값을 가져옵니다.
  {
    if (index >= Capacity)
      return std::nullopt; // 유효하지 않은 인덱스

    std::size_t currHead = head.load();
    std::size_t currTail = tail.load();

    if (currHead <= currTail) // 큐가 비어 있지 않을 때 원하는 위치의 값을 찾습니다.
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

    return std::nullopt; // 인덱스가 범위를 벗어났습니다.
  }

  void printQueue() // 큐의 모든 값을 출력합니다.
  {
    std::size_t currentHead = head.load(std::memory_order_relaxed);
    std::size_t currentTail = tail.load(std::memory_order_relaxed);
    while (currentHead != currentTail)
    {
      std::cout << buffer[currentHead] << " ";
      currentHead = IncrementIndex(currentHead);
    }
  }

  bool IsEmpty() const // 큐가 비어 있는지 확인합니다.
  {
    return head.load() == tail.load();
  }

private:
  std::array<T, Capacity> buffer;                     // 큐의 데이터를 저장하는 배열입니다.
  std::atomic<std::size_t> head;                      // 큐의 헤드 위치를 나타내는 원자적 변수입니다.
  std::atomic<std::size_t> tail;                      // 큐의 테일 위치를 나타내는 원자적 변수입니다.
  std::size_t IncrementIndex(std::size_t index) const // 인덱스를 증가시키는 메서드입니다.
  {
    return (index + 1) % Capacity;
  }
};
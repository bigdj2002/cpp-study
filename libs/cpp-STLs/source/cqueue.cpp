#include "cqueue.h"

void queue_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] std::queue
   * \details:
   *    - The std::queue class is a container adaptor that gives the programmer the functionality of a queue - specifically, a FIFO (first-in, first-out) data structure.
   *    - The class template acts as a wrapper to the underlying container - only a specific set of functions is provided.
   *    - The queue pushes the elements on the back of the underlying container and pops them from the front.
   *
   *    - template<class T, class Container = std::deque<T>> class queue;
   *       a. T - The type of the stored elements. The behavior is undefined if T is not the same type as Container::value_type.
   *       b. Container - The type of the underlying container to use to store the elements.
   *          1. The container must satisfy the requirements of SequenceContainer.
   *          2. Additionally, it must provide the following functions with the usual semantics: back(), front(), push_back(), pop_front()
   *          3. The standard containers std::deque and std::list satisfy these requirements.
   */

  std::queue<int> nums;
  nums.emplace(1);
  nums.emplace(3);
  nums.emplace(5);

  std::cout << nums.front() << ", " << nums.back() << std::endl;
  nums.pop();
  std::cout << nums.front() << ", " << nums.back() << std::endl;
  nums.pop();
  std::cout << nums.front() << ", " << nums.back() << std::endl;
  nums.pop();

  std::cout << "Size: " << nums.size() << std::endl;
  std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2] Ring buffer queue (using std::vector)
   */

  RingBufferQueue queue(5);

  queue.push(10);
  queue.push(20);
  queue.push(30);
  queue.push(40);
  queue.push(50);

  while (!queue.empty())
  {
    std::cout << queue.pop() << " ";
  }
  std::cout << std::endl;

  queue.push(60);
  queue.push(70);
  queue.push(80);

  while (!queue.empty())
  {
    std::cout << queue.pop() << " ";
  }
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] std::priority_queue
   *    - A priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.
   *    - A user-provided Compare can be supplied to change the ordering, e.g. using std::greater<T> would cause the smallest element to appear as the top().
   *    - Working with a priority_queue is similar to managing a heap in some random access container, with the benefit of not being able to accidentally invalidate the heap.
   *
   *    - template<class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>> class priority_queue;
   */

  std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  pq.emplace(1);
  pq.emplace(3);
  pq.emplace(5);
  pq.emplace(7);
  pq.emplace(9);

  std::cout << pq.top() << std::endl;
  pq.emplace(10); // O(log n)
  std::cout << pq.top() << std::endl;

  pq.pop();
  pq.pop();
  pq.pop();
  std::cout << pq.top() << std::endl;

  std::cout << "------------------------------------- [↑ Example 3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
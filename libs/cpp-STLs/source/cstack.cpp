#include "cstack.h"

void stack_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] std::stack
   * \details:
   *    - The std::stack class is a container adaptor that gives the programmer the functionality of a stack - specifically, a LIFO (last-in, first-out) data structure.
   *    - The class template acts as a wrapper to the underlying container - only a specific set of functions is provided.
   *    - The stack pushes and pops the element from the back of the underlying container, known as the top of the stack.
   *
   *    - template<class T, class Container = std::deque<T>> class stack;
   *       a. T - The type of the stored elements. The behavior is undefined if T is not the same type as Container::value_type.
   *       b. Container - The type of the underlying container to use to store the elements.
   *          1. The container must satisfy the requirements of SequenceContainer.
   *          2. Additionally, it must provide the following functions with the usual semantics: back(), push_back(), pop_back()
   *          3. The standard containers std::vector (including std::vector<bool>), std::deque and std::list satisfy these requirements.
   *          4. By default, if no container class is specified for a particular stack class instantiation, the standard container std::deque is used.
   */

  std::stack<int> nums;
  nums.emplace(1);
  nums.emplace(3);
  nums.emplace(5);

  std::cout << nums.top() << std::endl;
  nums.pop();
  std::cout << nums.top() << std::endl;
  nums.pop();
  std::cout << nums.top() << std::endl;
  nums.pop();

  std::cout << "Size: " << nums.size() << std::endl;
  std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2] Ring buffer stack (using std::vector)
   */

  RingBufferStack stack(5);

  stack.push(10);
  stack.push(20);
  stack.push(30);
  stack.push(40);
  stack.push(50);

  while (!stack.empty())
  {
    std::cout << stack.pop() << " ";
  }
  std::cout << std::endl;

  stack.push(60);
  stack.push(70);
  stack.push(80);

  while (!stack.empty())
  {
    std::cout << stack.pop() << " ";
  }
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}

#include "cthread_1.h"

void fn(int n)
{
  std::cout << "fn : " << n << std::endl;
}

void thread_example()
{
   /**
   * \brief: [1] std::thread
   */

  /** \example: #1 */
  std::cout << "Process start" << std::endl;
  std::thread t1(fn, 1);
  std::thread t2(fn, 2);
  // std::thread t2{std::move(t1)}; // Runtime error! (Need to remove 't1.join()' due to the loss thread ownership of t1)
  std::thread t3([]
                 { std::cout << "lamda thread" << std::endl; });

  t1.join();
  t2.join();
  t3.join();

  std::cout << "Process end" << std::endl;
}
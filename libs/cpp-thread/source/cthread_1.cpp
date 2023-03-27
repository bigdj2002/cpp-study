#include "cthread_1.h"

#define USE_JOIN_OR_DETACH 0 // 0: Join, 1: Detach

void fn(int n)
{
  std::cout << "fn : " << n << std::endl;
}

void thread_example_1()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] std::thread
   * \details: Constructor
   *    - 1) thread() noexcept; (since C++11)
   *    - 2) thread( thread&& other ) noexcept; (since C++11)
   *    - 3) template< class Function, class... Args >
   *         explicit thread( Function&& f, Args&&... args ); (since C++11)
   *    - 4) thread( const thread& ) = delete; (since C++11)
   * \details: Destructor
   *    - Destroys the thread object.
   *    - If *this has an associated thread (joinable() == true), std::terminate() is called.
   * \details: std::join
   *    - Blocks the current thread until the thread identified by *this finishes its execution.
   *    - The completion of the thread identified by *this synchronizes with the corresponding successful return from join().
   *    - No synchronization is performed on *this itself. Concurrently calling join() on the same thread object from multiple threads constitutes a data race that results in undefined behavior.
   * \details: std::detach
   *    - Separates the thread of execution from the thread object, allowing execution to continue independently.
   *    - Any allocated resources will be freed once the thread exits.
   *    - After calling detach *this no longer owns any thread.
   */

  /** \example: #1 */
  std::cout << "Process start" << std::endl;
  std::thread t1(fn, 1);
  std::thread t2(fn, 2);
  // std::thread t2{std::move(t1)}; // Runtime error! (Need to remove 't1.join()' due to the loss thread ownership of t1)
  std::thread t3([](int n = std::move(3))
                 { std::cout << "lamda thread : " << n << std::endl; });

  std::cout << "# of threads : " << std::thread::hardware_concurrency() << std::endl;
  std::cout << "Index of the current thread : " << std::this_thread::get_id() << std::endl;

  std::vector<std::thread> threads;
  for (int i = 0; i < 5; i++)
  {
    threads.emplace_back(fn, i + 5);
  }

#if USE_JOIN_OR_DETACH == 0
  t1.join();
  std::cout << "Joinable: " << t1.joinable() << std::endl;
  t2.join();
  t3.join();
  for (auto &thread : threads)
  {
    thread.join();
  }
#elif USE_JOIN_OR_DETACH == 1
  t1.detach();
  t2.detach();
  t3.detach();
#endif
  std::cout << "Process end" << std::endl;
  std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /* ---------------------------------------------------------------------------------------------------------- */
}
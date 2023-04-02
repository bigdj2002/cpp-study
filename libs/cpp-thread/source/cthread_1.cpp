#include "cthread_1.h"

#define USE_JOIN_OR_DETACH 0 // 0: Join, 1: Detach


void fn1(int n)
{
  std::cout << "fn1 : " << n << std::endl;
}

void fn2(int n, std::string & s) // string is quite expensive to copy → Reason to use reference for string
{
  std::cout << "fn2 : " << n << " " << s << std::endl;
}

void fn3(int &n)
{
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "fn1 : " << n << std::endl;
}

int fn4()
{
  return 3;
}

void fn5()
{
  // throw std::runtime_error("error"); // Compile ERROR! Cannot called as a result from thread exception. → Will call std::terminated 
}

void fn6()
{
  [[maybe_unused]] int fnNum = 2;
  static int globeNum = 0;
  thread_local int tlNum = 0;

  std::cout << "globalNum : " << globeNum << std::endl;
  std::cout << "threadLocalNum : " << tlNum << std::endl;

  globeNum++;
  tlNum++;
}

void caller()
{
  int num = 36;
  fn1(num);
}

void threadCaller(std::thread &t)
{
  int num = 36;
  t = std::thread(fn3, std::ref(num));
  t.join(); // Thread is safe to join in the same scope
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
  std::thread t1(fn1, 1);
  std::thread t2(fn1, 2);
  // std::thread t2{std::move(t1)}; // Runtime error! (Need to remove 't1.join()' due to the loss thread ownership of t1)
  std::thread t3([](int n = std::move(3))
                 { std::cout << "lamda thread : " << n << std::endl; });

  std::cout << "# of threads : " << std::thread::hardware_concurrency() << std::endl;
  std::cout << "Index of the current thread : " << std::this_thread::get_id() << std::endl;

  std::vector<std::thread> threads;
  for (int i = 0; i < 5; i++)
  {
    threads.emplace_back(fn1, i + 5);
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
  
  /**
   * \brief: [2] std::thread argument
   */

  /** \test: thread argument reference */
  int num1 = 36;
  std::string s = "Dongjae";
  std::thread t4(fn2, num1, std::ref(s));
  t4.join();
  std::cout << "------------------------------------- [↑ Example 2-1 ↑] -------------------------------------" << std::endl;

  /** \test: thread reference */
  caller(); // No problem
  std::thread t5;
  threadCaller(t5); // Output is strange number! To resolve this, delete below join code (And go to Line 32)
  // t5.join();
  std::cout << "------------------------------------- [↑ Example 2-2 ↑] -------------------------------------" << std::endl;

  /** \test: thread return  */
  int num2 = 0;
  std::thread t6([&num2]()
  { 
    num2 = fn4(); 
  });
  t6.join();
  std::cout << "RetVal : " << num2 << std::endl;
  std::cout << "------------------------------------- [↑ Example 2-3 ↑] -------------------------------------" << std::endl;

  /** \test: thread exception  */
  try
  {
    std::thread t(fn5);
    t.join();
  }
  catch(...)
  {
    std::cout << "catched" << std::endl;
  }
  std::cout << "------------------------------------- [↑ Example 2-4 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] thread_local
   * \details: It can be used when you want to use static variable in the current thread (ex. Singleton)
   */

  using namespace std::chrono_literals;

  [[maybe_unused]] int mainNum = 1;
  std::thread t7(fn6);
  std::this_thread::sleep_for(1s);
  std::thread t8(fn6);

  t7.join();
  t8.join();

  std::cout << "------------------------------------- [↑ Example 3-1 ↑] -------------------------------------" << std::endl;
}
#include "cthread.h"

#define USE_JOIN_OR_DETACH 0 // 0: Join, 1: Detach

void fn1(int n)
{
  std::cout << "fn1 : " << n << std::endl;
}

void fn2(int n, std::string &s) // string is quite expensive to copy → Reason to use reference for string
{
  std::cout << "fn2 : " << n << " " << s << std::endl;
}

void fn3(int &n)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
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

void fn4_task1(std::vector<int> &nums, std::size_t beginIdx, std::size_t endIdx, int &sum, std::mutex &mtx)
{
  const std::lock_guard<std::mutex> lck(mtx);
  for (std::size_t idx = beginIdx; idx < endIdx; ++idx)
  {
    sum += nums[idx];
  }
}

void fn4_task2(std::vector<int> &nums, std::size_t beginIdx, std::size_t endIdx, std::atomic<int> &sum)
{
  for (std::size_t idx = beginIdx; idx < endIdx; ++idx)
  {
    sum += nums[idx];
  }
}

void fn4_task3(std::vector<int> &nums, std::size_t beginIdx, std::size_t endIdx, int &sum)
{
  int localSum = 0;
  for (std::size_t idx = beginIdx; idx < endIdx; ++idx)
  {
    localSum += nums[idx];
  }
  sum = localSum;
}

void fn4_task4(std::vector<int> &nums, std::size_t beginIdx, std::size_t endIdx, int &sum)
{
  for (std::size_t idx = beginIdx; idx < endIdx; ++idx)
  {
    sum += nums[idx];
  }
}

void thread_example()
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
                 { num2 = fn4(); });
  t6.join();
  std::cout << "RetVal : " << num2 << std::endl;
  std::cout << "------------------------------------- [↑ Example 2-3 ↑] -------------------------------------" << std::endl;

  /** \test: thread exception  */
  try
  {
    std::thread t(fn5);
    t.join();
  }
  catch (...)
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
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  std::thread t8(fn6);

  t7.join();
  t8.join();

  std::cout << "------------------------------------- [↑ Example 3-1 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [4] parallel reduce
   */

  constexpr std::size_t count4 = 100000000;
  std::vector<int> nums4_1(count4, 1);

  int sum4_1 = 0;
  const auto start4_1 = std::chrono::steady_clock::now();

  for (std::size_t idx = 0; idx < count4; ++idx)
  {
    sum4_1 += nums4_1[idx];
  }

  const auto end4_1 = std::chrono::steady_clock::now();
  const std::chrono::duration<double> duration4_1 = end4_1 - start4_1;
  std::cout << "Time(sec) : " << duration4_1.count() << std::endl;
  std::cout << "Single for loop, Sum = " << sum4_1 << std::endl;

  std::cout << "------------------------------------- [↑ Example 4-1 ↑] -------------------------------------" << std::endl;

  std::vector<int> nums4_2(count4, 1);
  int sum4_2 = 0;
  const auto start4_2 = std::chrono::steady_clock::now();

  std::mutex mtx;
  std::thread t4_1(fn4_task1, std::ref(nums4_2), 0, count4 / 2, std::ref(sum4_2), std::ref(mtx));
  std::thread t4_2(fn4_task1, std::ref(nums4_2), count4 / 2, count4, std::ref(sum4_2), std::ref(mtx));

  t4_1.join();
  t4_2.join();

  const auto end4_2 = std::chrono::steady_clock::now();
  const std::chrono::duration<double> duration4_2 = end4_2 - start4_2;
  std::cout << "Time(sec) : " << duration4_2.count() << std::endl;
  std::cout << "Thread, Sum = " << sum4_2 << std::endl;

  std::cout << "------------------------------------- [↑ Example 4-2 ↑] -------------------------------------" << std::endl;

  std::vector<int> nums4_3(count4, 1);
  std::atomic<int> sum4_3a{0};
  std::atomic<int> sum4_3b{0};
  const auto start4_3 = std::chrono::steady_clock::now();

  std::thread t4_3(fn4_task2, std::ref(nums4_3), 0, count4 / 2, std::ref(sum4_3a));
  std::thread t4_4(fn4_task2, std::ref(nums4_3), count4 / 2, count4, std::ref(sum4_3b));

  t4_3.join();
  t4_4.join();

  const auto end4_3 = std::chrono::steady_clock::now();
  const std::chrono::duration<double> duration4_3 = end4_3 - start4_3;
  std::cout << "Time(sec) : " << duration4_3.count() << std::endl;
  std::cout << "Atomic, Sum = " << sum4_3a + sum4_3b << std::endl; // WHY SO SLOW? → Due to the false sharing!!

  std::cout << "------------------------------------- [↑ Example 4-3 ↑] -------------------------------------" << std::endl;

  std::vector<int> nums4_4(count4, 1);
  int sums4[2];
  const auto start4_4 = std::chrono::steady_clock::now();

  std::thread t4_5(fn4_task3, std::ref(nums4_4), 0, count4 / 2, std::ref(sums4[0]));
  std::thread t4_6(fn4_task3, std::ref(nums4_4), count4 / 2, count4, std::ref(sums4[1]));

  t4_5.join();
  t4_6.join();

  const auto end4_4 = std::chrono::steady_clock::now();
  const std::chrono::duration<double> duration4_4 = end4_4 - start4_4;
  std::cout << "Time(sec) : " << duration4_4.count() << std::endl;
  std::cout << "Atomic, Sum = " << sums4[0] + sums4[1] << std::endl; // WHY SO FAST? → ALSO Due to the NOT false sharing!!

  std::cout << "------------------------------------- [↑ Example 4-4 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [5] false sharing
   *   <Concept>   │    <Description>
   * ────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
   * False sharing │	Performance issue in multi-threaded systems where multiple threads access memory regions that share the same cache line
   *    Cause      │  Occurs when different threads modify variables located in the same cache line
   *    Impact     │  Leads to unnecessary cache invalidations and degraded performance
   *  Mitigation   │  Add padding between data to separate them into different cache lines
   *               │  Use atomic operations to ensure thread-safe access without cache line contention
   *               │  Separate data structures to avoid sharing cache lines
   *  Importance   │  Critical for optimizing performance in multi-threaded environments
   *
   *   <Solution>
   *    - Padding:
   *        Add sufficient padding between different data to ensure that each data has its own cache line.
   *        This can be achieved by adding padding bytes to adjust the positioning of data.
   *    - Use atomic operations:
   *        Use atomic operations to prevent concurrent access between different data and maintain cache coherence.
   *    - Separate data structures:
   *        Rearrange different data into separate structures to ensure that each data operates on independent cache lines.
   */

  std::vector<int> nums5_1(count4, 1);
  int sums5[17]; // For in different cache line (Over 64 byte)
  sums5[0] = 0;
  sums5[16] = 0;
  const auto start5_1 = std::chrono::steady_clock::now();

  std::thread t5_1(fn4_task4, std::ref(nums5_1), 0, count4 / 2, std::ref(sums5[0]));
  std::thread t5_2(fn4_task4, std::ref(nums5_1), count4 / 2, count4, std::ref(sums5[16]));

  t5_1.join();
  t5_2.join();

  const auto end5_1 = std::chrono::steady_clock::now();
  const std::chrono::duration<double> duration5_1 = end5_1 - start5_1;
  std::cout << "Time(sec) : " << duration5_1.count() << std::endl;
  std::cout << "Padding to solve F.S., Sum = " << sums5[0] + sums5[16] << std::endl; // WHY SO FAST? → A

  std::cout << "------------------------------------- [↑ Example 5 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
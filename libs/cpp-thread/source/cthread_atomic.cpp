#include "cthread_atomic.h"

void add_mutex(int &num, std::mutex &lck)
{
  for (int i = 0; i < 10000; i++)
  {
    const std::lock_guard<std::mutex> lock{lck};
    ++num;
  }
}

void add_atomic(std::atomic<int> &num)
{
  for (int i = 0; i < 10000; i++)
  {
    ++num;
  }
}

void push_func(ThreadSafeStack<int, 10> &stack, std::size_t stack_size)
{
  for (int i = 0; i < (int)stack_size / 2; ++i)
  {
    stack.push(i);
    std::cout << "Pushed: " << i << ", Stack: ";
    stack.print();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void pop_func(ThreadSafeStack<int, 10> &stack, std::size_t stack_size)
{
  for (int i = 0; i < (int)stack_size / 2; ++i)
  {
    auto result = stack.pop();
    if (result.has_value())
    {
      std::cout << "Popped: " << result.value() << ", Stack: ";
      stack.print();
    }
    else
    {
      std::cout << "Stack underflow" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}

void fn_atomic1(int &a, int &b, std::atomic<int> &n)
{
  a = 3;
  b = 5;
  n.store(1, std::memory_order_release);
}

void fn_atomic2(int &a, int &b, std::atomic<int> &n)
{
  while (n.load(std::memory_order_acquire) == 0)
  {
  }
  std::cout << "a: " << a << std::endl;
  std::cout << "b: " << b << std::endl;
}

void fn_atomic_cnt(std::atomic<int> &cnt)
{
  for (int i = 0; i < 1000; i++)
  {
    cnt.fetch_add(1, std::memory_order_relaxed);
  }
}

void write_x(std::atomic<bool> &x)
{
  x.store(true, std::memory_order_acq_rel);
}

void write_y(std::atomic<bool> &y)
{
  y.store(true, std::memory_order_acq_rel);
}

void read_x_then_y(std::atomic<bool> &x, std::atomic<bool> &y, std::atomic<int> &z)
{
  while (!x.load(std::memory_order_acq_rel))
  {
  }
  if (y.load(std::memory_order_acq_rel))
  {
    ++z;
  }
}

void read_y_then_x(std::atomic<bool> &x, std::atomic<bool> &y, std::atomic<int> &z)
{
  while (!y.load(std::memory_order_acq_rel))
  {
  }
  if (x.load(std::memory_order_acq_rel))
  {
    ++z;
  }
}

void thread_atomic_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] atomic introduction
   * \details:
   */

  int num1_a = 0;
  std::vector<std::thread> threads1_a, threads1_b;
  std::mutex lock1; // May slow..
  std::atomic<int> num1_b{0};

  auto start1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 4; i++)
  {
    threads1_a.emplace_back(add_mutex, std::ref(num1_a), std::ref(lock1));
    ;
  }

  for (auto &thread : threads1_a)
  {
    thread.join();
  }

  std::cout << num1_a << std::endl;
  auto end1 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time1 = end1 - start1;
  std::cout << "Mutex based thread: " << time1.count() * 1000 << std::endl;

  auto start2 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < 4; i++)
  {
    threads1_b.emplace_back(add_atomic, std::ref(num1_b));
  }

  for (auto &thread : threads1_b)
  {
    thread.join();
  }

  std::cout << num1_b << std::endl;
  auto end2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time2 = end2 - start2;
  std::cout << "Atomic based thread: " << time2.count() * 1000 << std::endl;

  std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2-1] methods of std::atomic
   * \note: Maybe a lock free system depend on compilers (cfg. std::atomic_flag: 100% lock free)
   * \details:
   *    - Each instantiation and full specialization of the std::atomic template defines an atomic type.
   *    - If one thread writes to an atomic object while another thread reads from it, the behavior is well-defined
   *      (see memory model for details on data races).
   *    - In addition, accesses to atomic objects may establish inter-thread synchronization and order non-atomic memory accesses as specified by std::memory_order.
   *    - std::atomic is neither copyable nor movable.
   *
   * \brief: [2-2] std::atomic_flag
   * \details:
   *    - std::atomic_flag is an atomic boolean type.
   *    - Unlike all specializations of std::atomic, it is guaranteed to be lock-free. (Check using is_lock_free())
   *    - Unlike std::atomic<bool>, std::atomic_flag does not provide load or store operations.
   */

  /** \example: Checking lock free */
  std::atomic<int> num2_a{0};
  std::atomic<float> num2_b{0.0f};
  std::atomic<int *> num2p;
  std::atomic<myStruct1> str2_a;
  // std::atomic<myStruct2> str2_b; // COMPILE ERROR..

  std::cout << std::boolalpha << num2_a.is_lock_free() << std::endl;
  std::cout << std::boolalpha << num2_b.is_lock_free() << std::endl;
  std::cout << std::boolalpha << num2p.is_lock_free() << std::endl;
  std::cout << std::boolalpha << str2_a.is_lock_free() << std::endl;
  // std::cout << std::boolalpha << str2_b.is_lock_free() << std::endl;

  std::cout << "------------------------------------- [↑ Example 2-1 ↑] -------------------------------------" << std::endl;

  /** \example: member functions */
  std::atomic<int> num2_c{0};
  int x2 = 42;
  [[maybe_unused]] int y2 = 0;
  [[maybe_unused]] bool flag2 = 0;

  num2_c.store(x2);                                   // MF for storing
  std::cout << "num: " << num2_c.load() << std::endl; // n = x; → COMPILE ERROR! (Deleted)

  x2 = num2_c.load(); // MF for loading
  std::cout << "x: " << x2 << std::endl;

  /** \note: Integer type only */
  num2_c.fetch_add(x2); // MF for adding (Same with 'n += x')
  std::cout << "num: " << num2_c.load() << std::endl;

  y2 = num2_c.exchange(x2); // MF for exchanging (y = num2_c, num2_c = x)
  std::cout << "x: " << x2 << ", y: " << y2 << ", num: " << num2_c.load() << std::endl;

  flag2 = num2_c.compare_exchange_strong(x2, y2);
  /** \details:
   * if (n == x){
   *   n = y;
   *   return true;
   * }
   * else{
   *   x = n;
   *   return false;
   * }
   */
  std::cout << "flag: " << flag2 << ", num: " << num2_c << ", x: " << x2 << ", y: " << y2 << std::endl;

  while (!num2_c.compare_exchange_weak(x2, y2))
  {
    std::cout << "Failed" << std::endl;
  }
  std::cout << "flag: " << flag2 << ", num: " << num2_c << ", x: " << x2 << ", y: " << y2 << std::endl;

  std::cout << "------------------------------------- [↑ Example 2-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] Lock free stack algorithm
   * \details:
   */

  constexpr std::size_t stack_size = 10;
  ThreadSafeStack<int, stack_size> stack;

  // Spawn two threads to push and pop from the stack concurrently
  std::thread push_thread(push_func, std::ref(stack), stack_size);
  std::thread pop_thread(pop_func, std::ref(stack), stack_size);

  push_thread.join();
  pop_thread.join();

  // Check if the remaining stack elements are correct
  assert(stack.get(0).has_value());
  assert(stack.get(stack_size - 1).has_value());
  assert(!stack.get(stack_size).has_value());

  std::cout << "------------------------------------- [↑ Example 3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [4] Memory order
   * \details:
   *    - In ARM & x86 architecture, the cost increases in the following order
   *      seq_cst > acq_rel > acquire = release > relaxed
   */

  int a4 = 0;
  int b4 = 0;
  std::atomic<int> n4{0};
  std::thread t4_a(fn_atomic1, std::ref(a4), std::ref(b4), std::ref(n4));
  std::thread t4_b(fn_atomic2, std::ref(a4), std::ref(b4), std::ref(n4));
  t4_a.join();
  t4_b.join();

  std::cout << "------------------------------------- [↑ Example 4-1 ↑] -------------------------------------" << std::endl;

  /** \ */
  std::atomic<int> cnt{0};
  std::vector<std::thread> ts4;

  for (int i = 0; i < 10; i++)
  {
    ts4.emplace_back(fn_atomic_cnt, std::ref(cnt));
  }

  for (auto &thread : ts4)
  {
    thread.join();
  }

  std::cout << "count: " << cnt << std::endl;

  std::cout << "------------------------------------- [↑ Example 4-2 ↑] -------------------------------------" << std::endl;

  std::atomic<bool> x = {false};
  std::atomic<bool> y = {false};
  std::atomic<int> z = {0};

  std::thread t4_c(write_x, std::ref(x));
  std::thread t4_d(write_y, std::ref(y));
  std::thread t4_e(read_x_then_y, std::ref(x), std::ref(y), std::ref(z));
  std::thread t4_f(read_y_then_x, std::ref(x), std::ref(y), std::ref(z));

  t4_c.join();
  t4_d.join();
  t4_e.join();
  t4_f.join();

  std::cout << z << std::endl; // z = 0 or 1 or 2
  /** 
   * \note: 0 is impossible in std::memory_order_seq_cst
  */

  assert(z.load() != 0); // will never happen

  std::cout << "------------------------------------- [↑ Example 4-3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
#include "cthread_sync.h"

void printThreadID()
{
  std::cout << "threadID : " << std::this_thread::get_id() << std::endl;
}

void plus10000(int &num, std::mutex &m)
{
  for (int i = 0; i < 10000; i++)
  {
    m.lock();
    num++;
    m.unlock();
  }
}

std::unique_lock<std::mutex> unlockTest(std::unique_lock<std::mutex> lck, int num)
{
  if (num == 10)
  {
    lck.unlock();
  }

  return lck;
}

void plus1(mInt &mi)
{
#if USE_LOCK_TYPE == 0
  mi.m.lock();
  std::cout << "std::mutex::lock/unlock" << std::endl;
  mi.num++;
  mi.m.unlock();
#elif USE_LOCK_TYPE == 1
  {
    const std::lock_guard<std::mutex> lock(mi.m);
    // Below codes in critical section from lock_guard
    // Use scope area cleverly :)
    std::cout << "std::lock_guard" << std::endl;
    mi.num++;
  } // Automatically unlocked
#elif USE_LOCK_TYPE == 2
  {
    std::unique_lock<std::mutex> lock(mi.m);
    std::cout << "std::unique_lock" << std::endl;
    mi.num++;
    lock = unlockTest(std::move(lock), mi.num); // Mutex lock can be managed as a resource
  }                                             // Automatically unlocked
#endif
}

void fn(std::mutex &m)
{
  const std::lock_guard<std::mutex> lck(m);
}

void fn(std::recursive_mutex &m)
{
  const std::lock_guard<std::recursive_mutex> lck(m);
}

void deadlockFn(std::mutex &m, std::recursive_mutex &mr)
{
  const std::lock_guard<std::mutex> lck(m);
  // const std::lock_guard<std::mutex> lck2(m); // Caused dead-lock
  // fn(std::ref(m)); // Caused self dead-lock
  fn(std::ref(mr)); // Solved self dead-lock using recursive_lock
}

void ab(std::mutex &ma, std::mutex &mb)
{
#if USE_SCLOPED_LOCK == 0
  const std::lock_guard<std::mutex> lcka(ma);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  const std::lock_guard<std::mutex> lckb(mb);
#elif USE_SCLOPED_LOCK == 1
  /** \example: Since c++17 */
  // const std::scoped_lock lck(ma, mb);
  // std::this_thread::sleep_for(std::chrono::seconds(1));

  // OR

  /** \example: Before c++17 */
  std::lock(ma, mb);
  std::lock_guard<std::mutex> lcka(ma, std::adopt_lock);
  std::lock_guard<std::mutex> lckb(mb, std::adopt_lock);
#endif
}

void ba(std::mutex &ma, std::mutex &mb)
{
#if USE_SCLOPED_LOCK == 0
  /** \example: Dead-lock with below */
  // const std::lock_guard<std::mutex> lckb(mb);
  // std::this_thread::sleep_for(std::chrono::microseconds(1));
  // const std::lock_guard<std::mutex> lcka(ma);

  /** \example: No dead-lock with below */
  const std::lock_guard<std::mutex> lcka(ma);
  std::this_thread::sleep_for(std::chrono::microseconds(1));
  const std::lock_guard<std::mutex> lckb(mb);
#elif USE_SCLOPED_LOCK == 1
  /** \example: Since c++17 */
  // const std::scoped_lock lck(mb, ma);
  // std::this_thread::sleep_for(std::chrono::seconds(1));

  // OR

  /** \example: Before c++17 */
  std::lock(mb, ma);
  std::lock_guard<std::mutex> lckb(mb, std::adopt_lock);
  std::lock_guard<std::mutex> lcka(ma, std::adopt_lock);
#endif
}

void setNum(smInt &mi, int num) // write operation (exclusive lock)
{
  // mi.mtx.lock();
  // mi.num = num;
  // mi.mtx.unlock();

  // OR

  /** \example: RAII for safety */
  std::lock_guard<std::shared_mutex> lck(mi.mtx);
  mi.num = num;
}

void printNum(smInt &mi) // read operation (shared lock)
{
  // mi.mtx.lock_shared();
  // std::cout << mi.num << std::endl;
  // mi.mtx.unlock_shared();

  // OR

  /** \example: RAII for safety */
  std::shared_lock<std::shared_mutex> lck(mi.mtx);
  std::cout << mi.num << std::endl;
}

void simple_do_once(std::once_flag &flag)
{
  std::call_once(flag, []()
                 { std::cout << "Simple example: called once\n"; });
}

void may_throw_function(bool do_throw)
{
  if (do_throw)
  {
    std::cout << "throw: call_once will retry\n"; // this may appear more than once
    throw std::exception();
  }
  std::cout << "Did not throw, call_once will not attempt again\n"; // guaranteed once
}

void do_once(bool do_throw, std::once_flag &flag)
{
  try
  {
    std::call_once(flag, may_throw_function, do_throw);
  }
  catch (...)
  {
  }
}

void cat_fn(std::once_flag &flag, std::unique_ptr<catSync> cp)
{
  std::call_once(flag, [&cp]()
                 { cp = std::make_unique<catSync>(); });
}

void thread_sync_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */
  /**
   * \brief: [1] std::mutex (Lock / Unlock)
   * \details:
   *    - The mutex class is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads.
   *    - mutex offers exclusive, non-recursive ownership semantics:
   *      a. A calling thread owns a mutex from the time that it successfully calls either lock or try_lock until it calls unlock.
   *      b. When a thread owns a mutex, all other threads will block (for calls to lock) or receive a false return value (for try_lock) if they attempt to claim ownership of the mutex.
   *      c. A calling thread must not own the mutex prior to calling lock or try_lock.
   *    - The behavior of a program is undefined if a mutex is destroyed while still owned by any threads, or a thread terminates while owning a mutex. The mutex class satisfies all requirements of Mutex and StandardLayoutType.
   *    - std::mutex is neither copyable nor movable.
   * \fn: lock()
   *    - Locks the mutex.
   *    - If another thread has already locked the mutex, a call to lock will block execution until the lock is acquired.
   *    - If lock is called by a thread that already owns the mutex, the behavior is undefined: for example, the program may deadlock. An implementation that can detect the invalid usage is encouraged to throw a std::system_error with error condition resource_deadlock_would_occur instead of deadlocking.
   *    - Prior unlock() operations on the same mutex synchronize-with (as defined in std::memory_order) this operation.
   * \fn: unlock()
   *    - Unlocks the mutex.
   *    - The mutex must be locked by the current thread of execution, otherwise, the behavior is undefined.
   *    - This operation synchronizes-with (as defined in std::memory_order) any subsequent lock operation that obtains ownership of the same mutex.
   * \fn: try_lock()
   *    - Tries to lock (i.e., takes ownership of) the associated mutex without blocking. Effectively calls mutex()->try_lock().
   *    - std::system_error is thrown if there is no associated mutex or if the mutex is already locked by this std::unique_lock.
   *    - Return: true if the ownership of the mutex has been acquired successfully, false otherwise.
   */

  // std::thread t1(printThreadID);
  // std::thread t2(printThreadID);
  // t1.join();
  // t2.join();

  int num1 = 0;
  std::mutex m1;
  std::thread t3(plus10000, std::ref(num1), std::ref(m1));
  std::thread t4(plus10000, std::ref(num1), std::ref(m1));
  t3.join();
  t4.join();
  std::cout << "Sum1 = " << num1 << std::endl;
  std::cout << "------------------------------------- [↑ Example 1-1 ↑] -------------------------------------" << std::endl;

  int num2 = 0;
  std::mutex m2;
  std::vector<std::thread> threads;
  for (int i = 0; i < 10; i++)
  {
    threads.emplace_back(std::thread(plus10000, std::ref(num2), std::ref(m2)));
  }

  for (auto &t : threads)
  {
    t.join();
  }
  std::cout << "Sum2 = " << num2 << std::endl;
  std::cout << "------------------------------------- [↑ Example 1-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2-1] std::lock_guard
   * \details:
   *    - The class lock_guard is a mutex wrapper that provides a convenient RAII-style mechanism for owning a mutex for the duration of a scoped block.
   *    - When a lock_guard object is created, it attempts to take ownership of the mutex it is given. When control leaves the scope in which the lock_guard object was created, the lock_guard is destructed and the mutex is released.
   *    - The lock_guard class is non-copyable.
   * \brief: [2-2] std::unique_lock
   * \details:
   *    - The class unique_lock is a general-purpose mutex ownership wrapper allowing deferred locking, time-constrained attempts at locking, recursive locking, transfer of lock ownership, and use with condition variables.
   *    - The class unique_lock is movable, but not copyable -- it meets the requirements of MoveConstructible and MoveAssignable but not of CopyConstructible or CopyAssignable.
   *    - The class unique_lock meets the BasicLockable requirements.
   *      If Mutex meets the Lockable requirements, unique_lock also meets the Lockable requirements (ex.: can be used in std::lock);
   *      If Mutex meets the TimedLockable requirements, unique_lock also meets the TimedLockable requirements.
   */

  mInt mi;
  std::thread t5(plus1, std::ref(mi));
  std::thread t6(plus1, std::ref(mi));
  t5.join();
  t6.join();
  std::cout << "Sum3 = " << mi.num << std::endl;
  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] Deadlock, scoped_lock (Since c++17)
   * \details:
   */

  std::mutex m3a;
  std::mutex m3b;
  std::recursive_mutex m3r;
  std::thread t3_a(deadlockFn, std::ref(m3a), std::ref(m3r));
  t3_a.join();

  std::thread t3_b(ab, std::ref(m3a), std::ref(m3b));
  std::thread t3_c(ba, std::ref(m3a), std::ref(m3b));
  t3_b.join();
  t3_c.join();

  std::cout << "Bye" << std::endl;

  std::cout << "------------------------------------- [↑ Example 3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [4] std::shared_mutex
   * \details:
   *    - The class shared_lock is a general-purpose shared mutex ownership wrapper allowing deferred locking, timed locking and transfer of lock ownership.
   *    - Locking a shared_lock locks the associated shared mutex in shared mode (to lock it in exclusive mode, std::unique_lock can be used).
   *    - The shared_lock class is movable, but not copyable – it meets the requirements of MoveConstructible and MoveAssignable but not of CopyConstructible or CopyAssignable.
   *    - Shared_lock meets the Lockable requirements.
   *    - If Mutex meets the SharedTimedLockable requirements, shared_lock also meets TimedLockable requirements.
   *    - In order to wait in a shared mutex in shared ownership mode, std::condition_variable_any can be used (std::condition_variable requires std::unique_lock and so can only wait in unique ownership mode).
   */

  smInt smi;
  std::thread t4_a(printNum, std::ref(smi));
  std::thread t4_b(setNum, std::ref(smi), 100);
  std::thread t4_c(printNum, std::ref(smi));
  std::thread t4_d(printNum, std::ref(smi));
  t4_a.join();
  t4_b.join();
  t4_c.join();
  t4_d.join();
  std::cout << "final num: " << smi.num << std::endl;

  std::cout << "------------------------------------- [↑ Example 4 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [5] std::call_once
   * \details:
   *    - How to use? Normaly, for initialization
   */

  std::once_flag flag1, flag2, flag3;
  std::thread t5_a(simple_do_once, std::ref(flag1));
  std::thread t5_b(simple_do_once, std::ref(flag1));
  std::thread t5_c(simple_do_once, std::ref(flag1));
  std::thread t5_d(simple_do_once, std::ref(flag1));
  t5_a.join();
  t5_b.join();
  t5_c.join();
  t5_d.join();

  std::thread t5_e(do_once, true, std::ref(flag2));
  std::thread t5_f(do_once, true, std::ref(flag2));
  std::thread t5_g(do_once, false, std::ref(flag2));
  std::thread t5_h(do_once, true, std::ref(flag2));
  t5_e.join();
  t5_f.join();
  t5_g.join();
  t5_h.join();

  std::cout << "------------------------------------- [↑ Example 5-1 ↑] -------------------------------------" << std::endl;

  std::unique_ptr<catSync> cp = nullptr;
  std::thread t5_i(cat_fn, std::ref(flag3), std::move(cp));
  std::thread t5_j(cat_fn, std::ref(flag3), std::move(cp));
  std::thread t5_k(cat_fn, std::ref(flag3), std::move(cp));
  std::thread t5_l(cat_fn, std::ref(flag3), std::move(cp));
  t5_i.join();
  t5_j.join();
  t5_k.join();
  t5_l.join();

  cp->speak();

  std::cout << "------------------------------------- [↑ Example 5-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
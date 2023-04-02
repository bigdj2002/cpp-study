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

#define USE_LOCK_TYPE 2 // 0: Normal lock, 1: Lock_guard, 2: unique_lock
void plus1(mInt &mi)
{
#if USE_LOCK_TYPE == 0
  mi.m.lock();
  std::cout << "std::mutex::lock/unlock" << std::endl;
  mi.num++;
  mi.m.unlock();
#elif USE_LOCK_TYPE == 1
  const std::lock_guard<std::mutex> lock(mi.m);
  // Below codes in critical section from lock_guard
  // Use scope area cleverly :)
  std::cout << "std::lock_guard" << std::endl;
  mi.num++;
#elif USE_LOCK_TYPE == 2
  const std::unique_lock<std::mutex> lock(mi.m);
  std::cout << "std::unique_lock" << std::endl;
  mi.num++;
#endif
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
   *    - The class unique_lock meets the BasicLockable requirements. If Mutex meets the Lockable requirements, unique_lock also meets the Lockable requirements (ex.: can be used in std::lock); if Mutex meets the TimedLockable requirements, unique_lock also meets the TimedLockable requirements.
   */

  mInt mi;
  std::thread t5(plus1, std::ref(mi));
  std::thread t6(plus1, std::ref(mi));
  t5.join();
  t6.join();
  std::cout << "Sum3 = " << mi.num << std::endl;
  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
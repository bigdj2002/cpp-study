#include "cthread_async.h"

int async_fn()
{
  std::cout << "async fn" << std::endl;
  return 42;
}

#define INSERTION_EXCEPTION 0
void prm_fn(std::promise<int> prm)
{
  std::this_thread::sleep_for(1s);
  try
  {
#if INSERTION_EXCEPTION
    throw std::runtime_error("Exception");
#else
    prm.set_value(42);
#endif
  }
  catch (...)
  {
    prm.set_exception(std::current_exception());
  }
}

void sfut_fn(std::shared_future<int> fut)
{
  std::cout << "Num: " << fut.get() << std::endl;
}

int add1(int n)
{
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2s);

  throw std::runtime_error("Dongjae error");
  return n + 1;
}

thread_local int localInt = 0;
void async_fn1()
{
  std::cout << ++localInt << std::flush;
}

void task_1s()
{
  std::this_thread::sleep_for(1s);
  std::cout << "task 1s" << std::endl;
}

void task_2s()
{
  std::this_thread::sleep_for(2s);
  std::cout << "task 2s" << std::endl;
}

void thread_async_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] std::async
   * \details:
   */

  std::future<int> fut1 = std::async(std::launch::async, async_fn);
  const int num1 = fut1.get();
  std::cout << "Return num: " << num1 << std::endl;

  std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2] std::future, std::promise
   * \details:
   */

  std::promise<int> prms2;
  std::future<int> fut2 = prms2.get_future();

  // prms2.set_value(42);
  std::thread t2(prm_fn, std::move(prms2));
  while (fut2.wait_for(0.5s) != std::future_status::ready)
  {
    std::cout << "Under process" << std::endl;
  }

  try
  {
    const int num2 = fut2.get();
    std::cout << "Num: " << num2 << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  t2.join();

  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] std::shared_future
   */

  std::promise<int> prms3;
  std::shared_future<int> fut3 = prms3.get_future();

  std::vector<std::jthread> t3s;
  for (int i = 0; i < 5; i++)
  {
    t3s.emplace_back(sfut_fn, fut3);
  }

  std::this_thread::sleep_for(1s);
  prms3.set_value(42);

  std::cout << "------------------------------------- [↑ Example 3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [4] std::async
   *    - The function template std::async runs the function f asynchronously
   *      (potentially in a separate thread which might be a part of a thread pool)
   *      and returns a std::future that will eventually hold the result of that function call.
   *         1) Behaves as if (2) is called with policy being std::launch::async | std::launch::deferred.
   *         2) Calls a function f with arguments args according to a specific launch policy policy (see below).
   */

  int num4 = 42;
  try
  {
    std::future<int> fut4 = std::async(add1, num4); // Execution asynchronously! (Not execution in different thread)
    int ret4 = fut4.get();
    std::cout << "Ret: " << ret4 << std::endl;
  }
  catch (const std::exception &e)
  {
    std::cout << "Exception: " << e.what() << std::endl;
  }

  for (int i = 0; i < 20; i++)
  {
    auto fut_async_fn1 = std::async(std::launch::async, async_fn1);
    // Is is better to consider callable object as a task!!
  }

  /** \details: std::future<T>::~future
   *    - Releases any shared state. This means
   *      * if the current object holds the last reference to its shared state, the shared state is destroyed;
   *      * the current object gives up its reference to its shared state;
   *    - These actions will not block for the shared state to become ready, except that they may block if all of the following are true:
   *      1. the shared state was created by a call to std::async,
   *      2. the shared state is not yet ready, and
   *      3. the current object was the last reference to the shared state.
   */

  // Below codes take 2s (fire and forget)
  auto fut4_a = std::async(std::launch::async, task_1s);
  auto fut4_b = std::async(std::launch::async, task_2s);

  // Below codes take 3s
  // std::async(std::launch::async, task_1s);
  // std::async(std::launch::async, task_2s);

  std::cout << "------------------------------------- [↑ Example 4 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
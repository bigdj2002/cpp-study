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

  std::promise<int> prms;
  std::future<int> fut2 = prms.get_future();

  // prms.set_value(42);
  std::thread t2(prm_fn, std::move(prms));
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
}
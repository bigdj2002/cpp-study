#include "cexception.h"

int g1 = 0;
int g2 = 0;
int g3 = 0;

int divide(int a, int b)
{
  if (b == 0)
  {
    throw std::runtime_error("Divide by 0"); // R-value
  }
  return a / b;
}

void f1()
{
  // RAII idiom
  std::unique_ptr<catEx> cp1 = std::make_unique<catEx>(); // No memory leak :)

  // catEx *cp2 = new catEx();
  std::cout << divide(10, 0) << std::endl;
  // delete cp2; // It is not called!! (Memory leak!!)
}

void f2()
{
  g1 = 1;
  [[maybe_unused]] int r1 = divide(10, 1);
  [[maybe_unused]] int r2 = divide(10, 0);
  [[maybe_unused]] int r3 = divide(10, 1);
  [[maybe_unused]] int r4 = divide(10, 2);
  g2 = 1;
}

void f3()
{
  try
  {
    int a = divide(10, 0);
    g3 = a;
  }
  catch (const std::exception &e)
  {
  }
}

void classCat(int a)
{
  if (a == 0)
  {
    throw catEx();
  }
}

void exception_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] cpp exception
   *    - try
   *    - catch
   *    - throw:
   */

  try
  {
    std::cout << divide(10, 0) << std::endl;
  }
  catch (const std::exception &e) // Reference
  {
    std::cout << e.what() << std::endl;
    std::cout << "Exception catched" << std::endl;
  }

  std::cout << "------------------------------------- [↑ Example 1-1 ↑] -------------------------------------" << std::endl;

  try
  {
    classCat(0);
  }
  catch (...) // = catch (const catEx &c)
  {
    std::cout << "cat catched" << std::endl;
  }

  std::cout << "------------------------------------- [↑ Example 1-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2] stack unwinding
   *    - The process of unraveling the execution stack of a program
   *    - The operation of stack unwinding can be described as follows:
   *       1. When an exception occurs in a program, the current function's call frame is removed from the execution stack.
   *          The call frame contains information about the function, local variables, return address, etc.
   *       2. Traversing up the stack, the call frames of the called functions are removed, and post-processing operations are performed for each function.
   *          Post-processing operations may include calling object destructors, releasing resources, etc.
   *       3. The stack is traversed upward until an exception handler is found.
   *          Once the exception handler is found, it handles the exception, and the program continues to execute normally.
   *       4. If no exception handler is found and the top of the stack is reached, the program terminates abnormally.
   */

  /** \example: No-exception safety */
  try
  {
    f1();
  }
  catch (const std::exception &e) // Reference
  {
    std::cout << e.what() << std::endl;
  }

  // f(); // Terminate called after throwing an instance of 'std::runtime_error'

  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] Exception safety guarantees
   *    - Basic exception safety:   No resource leak,     Allowed state change → Refer to global variable 'g1'
   *    - Strong exceptiopn safety: No resource leak, NOT allowed state change → Refer to global variable 'g2'
   *    - No-throw guarantee:       No exception (→ class destructor, swap/move operation, defalt constructor! WHY? just googling) → The reason of 'noexcept'
   *            VS
   *    - No-exception safety
   */

  /** \example: Basic exception safety, Strong exceptiopn safety */
  std::cout << "g1: " << g1 << std::endl;
  std::cout << "g2: " << g2 << std::endl;
  try
  {
    f2();
  }
  catch (const std::exception &e) // Reference
  {
    std::cout << e.what() << std::endl;
  }
  std::cout << "g1: " << g1 << std::endl;
  std::cout << "g2: " << g2 << std::endl;

  std::cout << "------------------------------------- [↑ Example 3-1 ↑] -------------------------------------" << std::endl;

  /** \example: No-throw guarantee */
  std::cout << "g3: " << g3 << std::endl;
  try
  {
    f3();
  }
  catch (const std::exception &e) // Reference
  {
    std::cout << e.what() << std::endl;
  }
  std::cout << "g3: " << g3 << std::endl;

  std::cout << "------------------------------------- [↑ Example 3-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [4] When should you use 'exception'?
   *    - No:  Regular error report
   *           Interal error handling
   *           nullptr, out of range
   *           Never happen
   *    - Yes: Constructor →
   *           Checking unsafety on server packet and file
   *
   *    - Google c++ guide: We do not use C++ exceptions.
   *      Pros:
   *      a. Exceptions allow higher levels of an application to decide how to handle "can't happen" failures in deeply nested functions, without the obscuring and error-prone bookkeeping of error codes.
   *      b. Exceptions are used by most other modern languages.
   *         Using them in C++ would make it more consistent with Python, Java, and the C++ that others are familiar with.
   *         Some third-party C++ libraries use exceptions, and turning them off internally makes it harder to integrate with those libraries.
   *      c. Exceptions are the only way for a constructor to fail.
   *         We can simulate this with a factory function or an Init() method, but these require heap allocation or a new "invalid" state, respectively.
   *      d. Exceptions are really handy in testing frameworks.
   *
   *      Cons:
   *      a. When you add a throw statement to an existing function, you must examine all of its transitive callers.
   *         Either they must make at least the basic exception safety guarantee, or they must never catch the exception and be happy with the program terminating as a result.
   *         For instance, if f() calls g() calls h(), and h throws an exception that f catches, g has to be careful or it may not clean up properly.
   *      b. More generally, exceptions make the control flow of programs difficult to evaluate by looking at code: functions may return in places you don't expect.
   *         This causes maintainability and debugging difficulties.
   *         You can minimize this cost via some rules on how and where exceptions can be used, but at the cost of more that a developer needs to know and understand.
   *      c. Exception safety requires both RAII and different coding practices.
   *         Lots of supporting machinery is needed to make writing correct exception-safe code easy.
   *         Further, to avoid requiring readers to understand the entire call graph, exception-safe code must isolate logic that writes to persistent state into a "commit" phase.
   *         This will have both benefits and costs (perhaps where you're forced to obfuscate code to isolate the commit).
   *         Allowing exceptions would force us to always pay those costs even when they're not worth it.
   *      d. Turning on exceptions adds data to each binary produced, increasing compile time (probably slightly) and possibly increasing address space pressure.
   *      e. The availability of exceptions may encourage developers to throw them when they are not appropriate or recover from them when it's not safe to do so.
   *         For example, invalid user input should not cause exceptions to be thrown.
   *         We would need to make the style guide even longer to document these restrictions!
   */

  std::cout << "------------------------------------- [↑ Example4 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
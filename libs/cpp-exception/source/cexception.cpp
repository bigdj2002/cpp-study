#include "cexception.h"

int divide(int a, int b)
{
  if (b == 0)
  {
    throw std::runtime_error("Divide by 0"); // R-value
  }
  return a / b;
}

void f()
{
  std::cout << divide(10, 0) << std::endl;
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

  try
  {
    f();
  }
  catch (const std::exception &e) // Reference
  {
    std::cout << e.what() << std::endl;
  }

  // f(); // Terminate called after throwing an instance of 'std::runtime_error'

  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
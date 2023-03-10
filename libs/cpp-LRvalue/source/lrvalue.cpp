#include "lrvalue.h"

void lrvalue_example()
{
  /**
   * \brief: Method to deliver arguements to function
   * \details: pass by value, pointer and reference
   * \note: Same assembly code (pass by pointer, reference)
   */

  int a = 0;
  fooV(a); // pass by value
  std::cout << a << std::endl;

  a = 0;
  fooP(&a); // pass by pointer
  std::cout << a << std::endl;

  a = 0;
  fooR(a); // pass by reference (More safer)
  std::cout << a << std::endl
            << std::endl;

  std::vector<int> vec;
  int a1 = 1;
  vec.push_back(a1);
  /** \def: push_back
   * void push_back( const T& value ); (~ C++20) → L-value reference (&)
   * constexpr void push_back( const T& value ); (C++20 ~)
   * void push_back( T&& value ); (since C++11 ~ C++20) → R-value reference (&&)
   * constexpr void push_back( T&& value ); (C++20 ~
   */

  /**
   * \brief: L-value? R-value?
   * \details: std::move → L-value to R-value
   */

  [[maybe_unused]] int b1 = 0;             // b1: L-value, 0: R-value
  [[maybe_unused]] int b2 = b1;            // b2b: L-value, b1: R-value
  [[maybe_unused]] int b3 = std::move(b2); // b3: L-value, std::move(b2): R-value

  std::string b4 = "abc";
  storeByValue(b4); // Copy operation in memory: #2
  std::cout << b4 << std::endl;
  storeByLRef(b4); // Copy operation in memory : #1
  std::cout << b4 << std::endl;

  b4 = "def";
  storeByRRef(std::move(b4)); // std::move(b4) : R-value, Copy operation in memory : #0
  storeByRRef("def");         // "abc" : R-value, Copy operation in memory : #0
  std::cout << std::endl;

  /**
   * \brief: std::move details
   */

  std::string c1 = "c++ coding";
  std::cout << "c1: " << c1 << std::endl;

  std::string c2 = std::move(c1); // std::move → Delivering resource ownership to other object
  std::cout << "c2: " << c2 << std::endl;
  std::cout << "c1: " << c1 << std::endl;
  storeByLRef(c2);
  std::cout << std::endl;

  caat kitty;
  std::string s = "Kitty";
  kitty.setNameR2(s);      // #1 copy
  kitty.setNameR2("nabi"); // #1 copy -> Not optimal!!
  kitty.setNameR3(s);      // #1 copy
  kitty.setNameR3("nabi"); // #0 copy -> Optimized (Copy elision optimization)
  std::cout << std::endl;

  /**
   * \brief: RVO (Return Value Optimization)
   * \details: One of the copy elision
   */

  std::string d1 = getString1(); // #0 copy, No need to move of ownership (move) ← RVO intervention
  std::cout << d1 << std::endl;
  std::string d2 = getString2(d1, true); // #0 copy (Due to the move constructor) ← No RVO intervention
  std::cout << d2 << std::endl;
  // Therefore, there is no need to be return value as std::move() type !!!
}

void fooV(int a)
{
  [[maybe_unused]] int b = a + 1;
}

void fooP(int *a)
{
  [[maybe_unused]] int b = *a + 1;
  *a = 100;
}

void fooR(const int &a)
{
  [[maybe_unused]] int b = a + 1;
  // a = 100; // Error!
}

void storeByValue(std::string s)
{
  std::string b = s;
}

void storeByLRef(std::string &s) // If const is added "const std::string &s", b1 and s are all to be "c++ coding"
{
  std::string b = s;
  std::string b1 = std::move(s);
  std::cout << b1 << std::endl;
}

void storeByRRef(std::string &&s)
{
  // At the moment, s is changed as L-value
  std::string b = std::move(s); // Therefore, s shall be changed again to R-value
  std::cout << b << std::endl;
}

std::string getString1()
{
  std::string s = "c++ coding";
  return s;
}

std::string getString2(std::string a, bool b)
{
  if (b)
  {
    a = "c++ coding";
  }
  return a; // No RVO
}
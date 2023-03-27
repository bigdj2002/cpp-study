#ifndef LAMDA_H_INCLUDED
#define LAMDA_H_INCLUDED

// c++ -> OOP + High performance (cache hit?)
// c++11 <- lamda expression (function objet, variable) -> functional programming

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

class plus
{
public:
  explicit plus(int a) : localVar{a} {}
  int operator()(int x) const // function call operator
  {
    return localVar + x;
  }

private:
  int localVar;
};

class cat1
{
public:
  explicit cat1(int age) : mAge{age} {}
  void speak() const
  {
    std::cout << "meow" << std::endl;
  }
  void test() const
  {
    // [this] → Can be access to member functions or vatiables
    auto lamda = [this]() 
    {
      std::cout << "lamda function" << std::endl;
      std::cout << mAge << std::endl;
      speak();
    };
    lamda();
  }
  int age()
  {
    return mAge;
  }

private:
  int mAge;
};

class FunctionObj
{
public:
  void operator()(int i)
  {
    std::cout << "functionObj " << i << std::endl;
  }
};

int lamda_example();

#endif
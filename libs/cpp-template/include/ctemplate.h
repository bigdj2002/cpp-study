#include <iostream>
#include <algorithm>
#include <vector>
#include <cxxabi.h>
#include <string>
#include <concepts>

void template_example();

template <typename T>
T addFunc(T a, T b)
{
  return a + b;
}

template <typename T, std::size_t N>
T nontype_mul(T a)
{
  return N * a;
}

template <typename... T>
void pack_print(T &&...args)
{
  (std::cout << ... << args) << std::endl;
}

template <typename T>
T foo(T a);

template <typename T>
class stack
{
public:
  void push(T elem)
  {
    mVec.emplace_back(std::move(elem));
  }
  bool pop(T &elem)
  {
    if (mVec.size() == 0)
    {
      return false;
    }
    elem = mVec[mVec.size() - 1];
    mVec.pop_back();
    return true;
  }

private:
  std::vector<T> mVec;
};

template <typename T>
using dongjaeKeys = std::vector<std::array<T, 64>>;

template <class T>
constexpr T pi = T(3.1415926535897932385L);

// 
template <typename U, typename T>
U find(U first, U last, const T &value)
{
  while (first != last)
  {
    if (*first == value)
    {
      return first;
    }
    first++;
  }
  return last;
}

template <typename T>
concept Addable1 = requires (T x)
{
  x + x;
  x - x;
};

template <typename T>
concept Addable2 = requires (T x)
{
  x + x;
};

template <typename T>
concept Summable = std::integral<T> || std::floating_point<T>;

template <typename T> requires Addable1<T>
T sum1(T a, T b)
{
  return a + b;
}

template <typename T> requires Addable2<T>
T sum2(T a, T b)
{
  return a + b;
}
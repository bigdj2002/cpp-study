#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <iostream>
#include <cstdint>
#include <array>
#include <vector>

int memory_example();

struct st1
{
  int a; // 4 bytes
  int b; // 4 bytes
}; // 8 bytes in total

struct st2
{
  long a;  // 8 bytes
  int b;   // 4 bytes
  short c; // 2 bytes
}; // 16 bytes in total (메모리가 가장 큰 자료형 변수의 바이트 배수)

/** 
 * \warning: Could be happen race condition or false sharing
 * \note: Since c++ 11, alignas specifier
 */
struct st3
{
  double d8;
  int i4a;
  int i4b;
  char c1;
}; // 24 bytess in total

struct alignas(32) st4
{
  double d8;
  int i4a;
  int i4b;
  char c1;
}; // 24 bytess in total

class cat
{
public:
  cat()
  {
    m_age = 6;
    m_weight = 12.5;
  }
  void printCat() { std::cout << static_cast<float>(m_age) + m_weight << std::endl; }

private:
  int m_age;      // 4 bytes;
  float m_weight; // 4 bytes;
};

#endif
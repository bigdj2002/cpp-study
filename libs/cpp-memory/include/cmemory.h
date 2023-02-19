#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <iostream>
#include <cstdint>
#include <array>

int memory_example();

struct st1
{
  int a; // 4 bytes
  int b; // 4 bytes
};

struct st2
{
  long a;  // 8 bytes
  int b;   // 4 bytes
  short c; // 2 bytes
};

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
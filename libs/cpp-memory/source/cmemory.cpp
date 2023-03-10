#include "cmemory.h"

int memory_example()
{
  int a = 0;
  int b = 3;
  int c = a + b;
  double d = 2.5;

  std::cout << "a: " << (long)&a << std::endl;
  std::cout << "b: " << (long)&b << std::endl;
  std::cout << "c: " << (long)&c << std::endl;
  std::cout << "d: " << (long)&d << std::endl;
  std::cout << std::endl;

  /* ----------------------------------------------------- */

  static_assert(sizeof(int) == 4, "int is 4 bytes");
  static_assert(sizeof(double) == 8, "double is 8 bytes");

  std::cout << sizeof(int) << std::endl;
  std::cout << sizeof(a) << std::endl;
  std::cout << sizeof(int8_t) << std::endl;
  std::cout << sizeof(int64_t) << std::endl;
  std::cout << std::endl;

  /* ----------------------------------------------------- */

  int e[5];
  std::array<int, 5> f;

  std::cout << sizeof(e) << std::endl;
  std::cout << sizeof(f) << std::endl;
  std::cout << std::endl;

  /* ----------------------------------------------------- */

  uint64_t ui8;
  uint64_t *ui64ptr = &ui8;

  std::cout << sizeof(ui64ptr) << std::endl;
  std::cout << (uint64_t)ui64ptr << std::endl;
  std::cout << std::endl;

  /* ----------------------------------------------------- */

  std::cout << sizeof(st1) << std::endl;
  std::cout << sizeof(st2) << std::endl;
  std::cout << sizeof(cat) << std::endl;

  cat cat1, cat2;
  cat *catptr = &cat1;
  std::cout << sizeof(cat1) << std::endl;
  std::cout << sizeof(cat2) << std::endl;
  std::cout << sizeof(catptr) << std::endl;
  std::cout << std::endl;

  /* ----------------------------------------------------- */

  std::cout << sizeof(st3) << std::endl;
  std::cout << sizeof(st4) << std::endl;
  std::cout << std::endl;

  /**
   * \brief: Stack memory
   * \details: order: depent on stack call 
   */

  return 0;
}
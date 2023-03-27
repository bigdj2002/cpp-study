#include "cstring.h"

void printString(const std::string &s)
{
  std::cout << s << std::endl;
}

void printStringView(const std::string_view s)
{
  std::cout << s << std::endl;
}

void string_example()
{
  /**
   * \brief: [1] char
   */

  int code = 65;
  std::cout << (char)code << std::endl;

  char s1[7] = {'n', 'o', '\0', 'c', 'o', 'p', 'e'};
  std::cout << s1 << " ";
  std::cout << sizeof(s1) << " ";
  std::cout << strlen(s1) << " "; // Before null character
  std::cout << std::endl;

  char s2[] = "nocope";
  s2[0] = 'd';
  std::cout << s2 << " ";
  std::cout << sizeof(s2) << " ";
  std::cout << strlen(s2) << " "; // Before null character
  std::cout << std::endl;

  // char *s3 = "nocope"; // Complile error! forbided converting a string constant to ‘char*’
  const char *s3 = "nocope";
  // s3[0] = 'c'; // Compile error! Stored in read-only memory
  std::cout << s3 << " ";
  std::cout << sizeof(s3) << " ";
  std::cout << strlen(s3) << " "; // Before null character
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;




  /**
   * \brief: [2] std::string
   */

  std::string c1 = "nocope";
  std::cout << c1 << " ";
  // std::cout << strlen(c1) << std::endl; // Compile error! Cannot convert ‘std::string’
  std::cout << sizeof(c1) << " ";
  std::cout << c1.size() << " ";
  std::cout << std::endl;

  std::string c2("no\0cope", 7);
  std::cout << c2 << " ";
  std::cout << sizeof(c2) << " ";
  std::cout << c2.size() << " ";
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;




  /**
   * \brief: [3] std::string_view
   */

  [[maybe_unused]] char c3_1[] = "nocopeStack";
  [[maybe_unused]] const char *c3_2 = "nocopeReadOnly";
  [[maybe_unused]] std::string c3_3 = "nocopeHeap";

  printString(c3_1); // Performance ↓, Due to the needs a allocation temporary memory in Heap
  printString(c3_2); // Performance ↓, Due to the needs a allocation temporary memory in Heap
  printString(c3_3); // No problem :)
  printStringView(c3_1); // Same performance! Resolved above mentioned problem :)
  printStringView(c3_2); // Same performance! Resolved above mentioned problem :)
  printStringView(c3_3);
  printStringView("nocopeLiteral"); // Similar to std::span !
  std::cout << "------------------------------------- [↑ Example 3 ↑] -------------------------------------" << std::endl;
}
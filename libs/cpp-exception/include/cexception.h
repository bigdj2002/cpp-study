#include <iostream>

void exception_example();

class catEx
{
public:
  catEx()
  {
    std::cout << "catEx constructor" << std::endl;
  }
  ~catEx()
  {
    std::cout << "catEx destructor" << std::endl;
  }
};
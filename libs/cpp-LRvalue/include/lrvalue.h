#include <iostream>
#include <vector>
#include <string>

void lrvalue_example();

void fooV(int a);
void fooP(int *a);
void fooR(const int &a);

void storeByValue(std::string s);
void storeByLRef(std::string &s);
void storeByRRef(std::string &&s);

std::string getString1();
std::string getString2(std::string a, bool b);

class caat
{
public:
  void setName1(std::string name)
  {
    mName = name;
    std::cout << name << std::endl;
    std::cout << mName << std::endl;
  }
  void setNameR1(std::string &name)
  {
    mName = std::move(name);
    std::cout << name << std::endl;
    std::cout << mName << std::endl;
  }
  void setNameR2(const std::string &name)
  {
    mName = std::move(name);
    std::cout << name << std::endl;
    std::cout << mName << std::endl;
  }
  void setNameR3(std::string name)
  {
    mName = std::move(name);
    std::cout << name << std::endl;
    std::cout << mName << std::endl;
  }

private:
  std::string mName;
};
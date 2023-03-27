#include <set>
#include <iostream>

void set_example();

class cat_set
{
public:
  cat_set(int age, std::string name) : mAge{age}, mName{std::move(name)} {}
  void speak() const
  {
    std::cout << mAge << " " << mName << std::endl;
  }
  int age() const
  {
    return mAge;
  }
  const std::string &name() const // Former const: To fix object value, Latter const: To fix return value
  {
    return mName;
  }

private:
  int mAge;
  std::string mName;
};

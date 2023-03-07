#include <vector>
#include <iostream>
#include <string>

int vector_example();

class Cat1
{
public:
  explicit Cat1(int age) : mAge{age} {}
  explicit Cat1(std::string name) : mName{std::move(name)} {}
  explicit Cat1(std::string name, int age) : mName{std::move(name)}, mAge{age} {}
  ~Cat1() {}

  void speak1() const
  {
    std::cout << "meow[" << mAge << "]  ";
  }
  void speak2() const
  {
    std::cout << "meow[" << mName << " " << mAge << "]  ";
  }

private:
  std::string mName;
  int mAge;
};

/* INFO 1: memory
Pointer -> Stored in STACK MEMORY
Array -> (Sequantialy) Stored in HEAP MEMORY
*/

/* INFO: Time complexity
The complexity (efficiency) of common operations on vectors is as follows:
- Random access - constant O(1)
- Insertion or removal of elements at the end - amortized constant O(1)
- Insertion or removal of elements - linear in the distance to the end of the vector O(n)
*/

class Cat2
{
public:
  explicit Cat2(int age) : mAge{age}
  {
    // std::cout << mAge << ": Cat2 constructor" << std::endl;
  }
  explicit Cat2(std::string name) : mName{std::move(name)}
  {
    // std::cout << mName << ": Cat2 constructor" << std::endl;
  }
  explicit Cat2(std::string name, int age) : mName{std::move(name)}, mAge{age}
  {
    // std::cout << mName << mAge << ": Cat2 constructor" << std::endl;
  }
  ~Cat2() noexcept
  {
    // std::cout << mName << ": ~Cat2()" << std::endl;
  }

  Cat2(const Cat2 &other) : mName(other.mName) // Copy assignment
  {
    // std::cout << mName << ": Cat2 Copy constructor" << std::endl;
  }
  Cat2(Cat2 &&other) noexcept : mName{std::move(other.mName)} // Move assignment (NO except!!)
  {
    // std::cout << mName << ": Cat2 Move constructor" << std::endl;
  }

private:
  std::string mName;
  int mAge;
};
#include <iostream>
#include <memory>
#include <vector>

void pointer_example();

class Animal
{
};

class cat_pointer : public Animal
{
public:
  cat_pointer(int age) : mAge{age}
  {
    std::cout << "cat constructor" << std::endl;
  }
  cat_pointer() : mAge{0}
  {
    std::cout << "cat constructor" << std::endl;
  }
  ~cat_pointer() noexcept
  {
    std::cout << "cat destructor" << std::endl;
  }

  void speak()
  {
    std::cout << "Meow~~" << std::endl;
  }

public:
  std::shared_ptr<cat_pointer> mVar;
  std::shared_ptr<cat_pointer> mFriend;

private:
  int mAge;
};

class dog_pointer : public Animal
{
};

class Zoo
{
public:
  Zoo(int n)
  {
    if (n == 1)
      mAnimal = std::make_unique<cat_pointer>();
    else
      mAnimal = std::make_unique<dog_pointer>();
  }

private:
  std::unique_ptr<Animal> mAnimal;
};
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
  cat_pointer(int age) : mAge{age}, mVar2{nullptr}
  {
    std::cout << "cat constructor" << std::endl;
  }
  cat_pointer() : cat_pointer(0) {}

  explicit cat_pointer(short n) : mAge{0}, mVar2{std::make_unique<int>(n)}
  {
    std::cout << "cat constructor" << std::endl;
  }
  
  ~cat_pointer() noexcept
  {
    std::cout << "cat destructor" << std::endl;
  }

  void speak()
  {
    std::cout << "Meow~~" << mAge << std::endl;
  }

public:
  std::shared_ptr<cat_pointer> mVar1;
  
  std::shared_ptr<cat_pointer> mFriend1;
  std::weak_ptr<cat_pointer> mFriend2;

private:
  int mAge;
  std::unique_ptr<int> mVar2;
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
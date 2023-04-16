#include <iostream>
#include <array>
#include <random>

/** \note: Reason to use inheritance
 *    - Class relationship
 *    - Code reuse
 *    - Class interface consistency (abstract / interface, pure virtual function)
 *    - Dynamic function binding (virtual function, virtual table)
 */

void inherance_example();

class animal
{
public:
  animal()
  {
    std::cout << "animal constructor" << std::endl;
  }

  /** \note: Base class destructor
   *    - It shoud use virtual public and protected
   *    - Because the destructor of leaf class is not called!
   */
  // ~animal()
  virtual ~animal() = default;
  // {
  //   std::cout << "animal destructor" << std::endl;
  // }

  virtual void speak()
  {
    std::cout << "animal [pointing VT]" << std::endl;
  }

  virtual void speak2() = 0;

  void sleep() const
  {
    std::cout << "I'm sleeping" << std::endl;
  }

private:
  double height;
};

// class human : public animal
class human
{
public:
  void dirveCar() const
  {
    std::cout << "I'm driving" << std::endl;
  }
};

class catInh : public animal
{
public:
  catInh()
  {
    std::cout << "cat constructor" << std::endl;
  }
  ~catInh() = default;
  // {
  //   std::cout << "cat destructor" << std::endl;
  // }

  void speak() override
  {
    std::cout << "meow~ [pointing VT]" << std::endl;
  }

  void speak2() override
  {
    std::cout << "meow2~ [pointing VT]" << std::endl;
  }

private:
  double weight;
};

class dogInh : public animal
{
public:
  dogInh()
  {
    std::cout << "dog constructor" << std::endl;
  }
  ~dogInh() = default;
  // {
  //   std::cout << "dog destructor" << std::endl;
  // }

  void speak() override
  {
    std::cout << "bark!" << std::endl;
  }

  void speak2() override
  {
    std::cout << "bark2! [pointing VT]" << std::endl;
  }
};

class lion1 : public animal
{
public:
  lion1() { std::cout << "lion constructor" << std::endl; }
  virtual ~lion1() = default;
  virtual void speak() { std::cout << "lion!" << std::endl; }
  void speak2() override { std::cout << "lion2!" << std::endl; }

private:
  double lionData;
};

class tiger1 : public animal
{
public:
  tiger1() { std::cout << "tiger constructor" << std::endl; }
  virtual ~tiger1() = default;
  virtual void speak() { std::cout << "tiger!" << std::endl; }
  void speak2() override { std::cout << "tiger2!" << std::endl; }

private:
  double tigerData;
};

class lion2 : virtual public animal
{
public:
  lion2() { std::cout << "lion constructor" << std::endl; }
  virtual ~lion2() = default;
  virtual void speak() { std::cout << "lion!" << std::endl; }
  void speak2() override { std::cout << "lion2!" << std::endl; }

private:
  double lionData;
};

class tiger2 : virtual public animal
{
public:
  tiger2() { std::cout << "tiger constructor" << std::endl; }
  virtual ~tiger2() = default;
  virtual void speak() { std::cout << "tiger!" << std::endl; }
  void speak2() override { std::cout << "tiger2!" << std::endl; }

private:
  double tigerData;
};

class liger : public lion1, public tiger1
{
public:
  liger() { std::cout << "liger constructor" << std::endl; }
  virtual ~liger() = default;
  void speak() override { std::cout << "liger!" << std::endl; }
  void speak2() override { std::cout << "liger2!" << std::endl; }

private:
  double ligerData;
};
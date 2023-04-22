#include <iostream>
#include <array>
#include <random>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>

/** \note: Reason to use inheritance
 *    - Class relationship
 *    - Code reuse
 *    - Class interface consistency (abstract / interface, pure virtual function)
 *    - Dynamic function binding (virtual function, virtual table)
 */

void inherance_example();

class animalInh
{
public:
  animalInh()
  {
    std::cout << "animal constructor" << std::endl;
  }

  /** \note: Base class destructor
   *    - It shoud use virtual public and protected
   *    - Because the destructor of leaf class is not called!
   */
  // ~animal()
  virtual ~animalInh() = default;
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

class animalInh2
{
public:
  animalInh2() = default;
  virtual ~animalInh2() = default;
  animalInh2 operator=(animalInh2 other) = delete;

  virtual void speak()
  {
    std::cout << "animal2 [pointing VT]" << std::endl;
  }

protected:
  animalInh2(const animalInh2 &other) = default;

public:
  double animal2Data = 0.0f;
};

inline bool operator==(const animalInh2 &lhs, const animalInh2 &rhs)
{
  std::cout << "animal comp" << std::endl;
  return lhs.animal2Data == rhs.animal2Data;
}

// class human : public animal
class human
{
public:
  void dirveCar() const
  {
    std::cout << "I'm driving" << std::endl;
  }
};

class catInh : public animalInh
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

class dogInh : public animalInh
{
public:
  dogInh(double d) : dogData{d} {};
  dogInh()
  {
    std::cout << "dog constructor" << std::endl;
  }
  virtual ~dogInh() = default;
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

private:
  double dogData;
};

class doginh2 : public animalInh2
{
public:
  doginh2(double d) : dogData{d} {};
  void speak() override { std::cout << "bark2!" << std::endl; }

public:
  double dogData;
};

inline bool operator==(const doginh2 &lhs, const doginh2 &rhs)
{
  std::cout << "dog comp" << std::endl;
  return lhs.dogData == rhs.dogData;
}

class lion1 : public animalInh
{
public:
  lion1() { std::cout << "lion constructor" << std::endl; }
  virtual ~lion1() = default;
  virtual void speak() { std::cout << "lion!" << std::endl; }
  void speak2() override { std::cout << "lion2!" << std::endl; }

private:
  double lionData;
};

class tiger1 : public animalInh
{
public:
  tiger1() { std::cout << "tiger constructor" << std::endl; }
  virtual ~tiger1() = default;
  virtual void speak() { std::cout << "tiger!" << std::endl; }
  void speak2() override { std::cout << "tiger2!" << std::endl; }

private:
  double tigerData;
};

class lion2 : virtual public animalInh
{
public:
  lion2() { std::cout << "lion constructor" << std::endl; }
  virtual ~lion2() = default;
  virtual void speak() { std::cout << "lion!" << std::endl; }
  void speak2() override { std::cout << "lion2!" << std::endl; }

private:
  double lionData;
};

class tiger2 : virtual public animalInh
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

class animalInh3
{
public:
  virtual void speak()
  {
    std::cout << "animal" << std::endl;
  }

  virtual ~animalInh3() = default;

private:
  double animalData;
};

class catInh3 : public animalInh3
{
public:
  void speak() override
  {
    std::cout << "meow" << std::endl;
  }
  void knead()
  {
    std::cout << "kkuk kkuk" << std::endl;
  }

private:
  double catData;
};

class dogInh3 : public animalInh3
{
public:
  void speak() override
  {
    std::cout << "bark" << std::endl;
  }
  void wagTail()
  {
    std::cout << "wagging" << std::endl;
  }

private:
  double dogData;
};

class catInh4
{
public:
  catInh4(std::string name, int age) : mName{std::move(name)}, mAge{age} {};
  void print(std::ostream &os)
  {
    os << mName << " " << mAge << std::endl;
  }
  void setFromStream(std::istream &is)
  {
    is >> mName >> mAge;
  }

private:
  std::string mName;
  int mAge;
};
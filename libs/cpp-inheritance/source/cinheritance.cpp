#include "cinheritance.h"

void inherance_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] class
   *    - public ⊃ protected ⊃ private
   * class A
   * {
   * public:
   *   int x;
   * protected:
   *   int y;
   * private:
   *   int z;
   * };
   * class B : public A
   * {
   *   // x is public
   *   // y is protected
   *   // z is not accessible from B
   * };
   * class C : protected A
   * {
   *   // x is protected
   *   // y is protected
   *   // z is not accessible from C
   * };
   * class D : private A    // 'private' is default for classes
   * {
   *   // x is private
   *   // y is private
   *   // z is not accessible from D
   * };
   *    - IMPORTANT NOTE: Classes B, C and D all contain the variables x, y and z. It is just question of access.
   */

  human dongjae;
  dongjae.dirveCar();
  // dongjae.sleep();

  std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2] virtual function
   */

  /** \example: #2-1 */
  catInh cat;

  /** \example: #2-2 */
  // animal *animalPtr = new animal();
  // delete animalPtr;

  /** \example: #2-3 */
  // catInh *catPtr = new catInh();
  // delete catPtr;

  /** \example: #2-4 */
  // animal *polyCat = new catInh();
  // delete polyCat;

  /** \example: #2-5 (Dynamic or Runtime) polymorphism */
  // animal *polyAnimal;
  // polyAnimal = new catInh();
  // polyAnimal->speak();
  // delete polyAnimal;

  // polyAnimal = new animal();
  // polyAnimal->speak();
  // delete polyAnimal;

  /** \example: #2-6 (Dynamic or Runtime) polymorphism */
  std::array<animal *, 5> animals; // It is better to use smart pointer
  for (auto &animal : animals)
  {
    std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(1, 2);
    int random_int = dist(rng);
    if (random_int == 1)
      animal = new catInh();
    else
      animal = new dogInh();
  }
  for (auto &animal : animals)
  {
    animal->speak();
    delete animal;
  }

  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] virtual table
   */

  /** \note: Added address memory of virtual function (Reason of additional 8bytes)
   *         Pointer of the above address points virtual table of them
   */
  std::cout << "animal size: " << sizeof(animal) << std::endl;
  std::cout << "cat size: " << sizeof(catInh) << std::endl;

  animal *polyAnimal2 = new catInh;
  polyAnimal2->speak();
  delete polyAnimal2;

  std::cout << "------------------------------------- [↑ Example 3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [4] pure virtual table (For Abstract or Interface class)
   *    - It cannot generate any object by itself
   *    - Highly recommended to NOT use member variables in interface class (To be more flexible)
   */

  // animal abs; // compile ERROR!

  std::cout << "------------------------------------- [↑ Example 4 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [5] Multiple inheritance
   */

  

  std::cout << "------------------------------------- [↑ Example 5 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
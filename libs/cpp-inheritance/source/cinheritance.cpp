#include "cinheritance.h"

void inherance_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] class
   *    - public ⊃ protected ⊃ private
   *    - Example code:
   *        class A
   *        {
   *        public:
   *            int x;
   *        protected:
   *            int y;
   *        private:
   *            int z;
   *        };
   *        class B : public A
   *        {
   *            // x is public
   *            // y is protected
   *            // z is not accessible from B
   *        };
   *        class C : protected A
   *        {
   *            // x is protected
   *            // y is protected
   *            // z is not accessible from C
   *        };
   *        class D : private A  // 'private' is default for classes
   *        {
   *            // x is private
   *            // y is private
   *            // z is not accessible from D
   *        };
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
  std::cout << "------------------------------------- [↑ Example 2-1 ↑] -------------------------------------" << std::endl;

  /** \example: #2-2 */
  // animal *animalPtr = new animal();
  // delete animalPtr;
  std::cout << "------------------------------------- [↑ Example 2-2 ↑] -------------------------------------" << std::endl;

  /** \example: #2-3 */
  catInh *catPtr = new catInh();
  delete catPtr;
  std::cout << "------------------------------------- [↑ Example 2-3 ↑] -------------------------------------" << std::endl;

  /** \example: #2-4 */
  animal *polyCat = new catInh();
  delete polyCat;
  std::cout << "------------------------------------- [↑ Example 2-4 ↑] -------------------------------------" << std::endl;

  /** \example: #2-5 (Dynamic or Runtime) polymorphism */
  animal *polyAnimal;
  polyAnimal = new catInh();
  polyAnimal->speak();
  delete polyAnimal;

  // polyAnimal = new animal();
  // polyAnimal->speak();
  // delete polyAnimal;
  std::cout << "------------------------------------- [↑ Example 2-5 ↑] -------------------------------------" << std::endl;

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

  std::cout << "------------------------------------- [↑ Example 2-6 ↑] -------------------------------------" << std::endl;

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

  /** \example: #5-1 */
  liger liger1;
  liger1.speak();
  /** \note: total 40bytes =
   *         lion1  vt (8) + lionData  (8) +
   *         tiger1 vt (8) + tigerData (8) +
   *                       + ligerData (8) */
  std::cout << sizeof(liger1) << std::endl;
  std::cout << "------------------------------------- [↑ Example 5-1 ↑] -------------------------------------" << std::endl;

  /** \example: Diamond inheritance #5-2 */
  liger *polyAnimal3 = new liger;
  polyAnimal3->speak();
  /** \note: total 8bytes = ligerData (8) */
  std::cout << sizeof(polyAnimal3) << std::endl;
  delete polyAnimal3;

  std::cout << "------------------------------------- [↑ Example 5-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [6] virtual inheritance
   */

  /** \note: total 24bytes =
   *         animal  vt (8) + animalData  (8) + lionData (8)
   *         -------------------------
   *         * animal vt → (Points to lion vt: lion data can be used)
   *         -------------------------
   *           animal data
   *         -------------------------
   *           lion data
   *         -------------------------
   */
  std::cout << sizeof(lion1) << std::endl;
  /** \note: total 32bytes =
   *         animal  vt (8) + animalData  (8) + lion vt (8) + lionData (8)
   *         -------------------------
   *         * lion vt
   *         -------------------------
   *           lion data
   *         -------------------------
   *         * animal vt  → (Points to lion vt: lion data can be used..
   *                         BUT!! vt doesn't know where lion data is.
   *                         Therefore additional offset is needed to indicate their location in memory.
   *                         thunk function, des)
   *         -------------------------
   *           animal data
   *         -------------------------
   */
  std::cout << sizeof(lion2) << std::endl;

  animal *polyAnimal4 = new lion2();
  polyAnimal4->speak(); // call thunk function in lion vt!
  delete polyAnimal4;

  /** \remark: Figure for [Diamond inheritance VS Linear inheritance]
   * ------------------------------------------------------------------
   *       animal                * animal vt \ animal data
   *       /    \                  lion data
   *    lion    tiger            * animal vt \ animal data
   *       \    /                  tiger data
   *        liger                  liger data
   * ------------------------------------------------------------------
   *       animal                * lion vt \ lion data
   *       /    \ (virtual)      * tiger vt \ tiger data
   *    lion    tiger              liger data
   *       \    /                * animal vt \ animal data
   *        liger
   * ------------------------------------------------------------------
   */

  std::cout << "------------------------------------- [↑ Example 6 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [7] object slicing
   */

  

  std::cout << "------------------------------------- [↑ Example 7 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
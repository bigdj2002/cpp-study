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
  animalInh *polyCat = new catInh();
  delete polyCat;
  std::cout << "------------------------------------- [↑ Example 2-4 ↑] -------------------------------------" << std::endl;

  /** \example: #2-5 (Dynamic or Runtime) polymorphism */
  animalInh *polyAnimal;
  polyAnimal = new catInh();
  polyAnimal->speak();
  delete polyAnimal;

  // polyAnimal = new animal();
  // polyAnimal->speak();
  // delete polyAnimal;
  std::cout << "------------------------------------- [↑ Example 2-5 ↑] -------------------------------------" << std::endl;

  /** \example: #2-6 (Dynamic or Runtime) polymorphism */
  std::array<animalInh *, 5> animals; // It is better to use smart pointer
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
  std::cout << "animal size: " << sizeof(animalInh) << std::endl;
  std::cout << "cat size: " << sizeof(catInh) << std::endl;

  animalInh *polyAnimal2 = new catInh;
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
   *         lion1  VT (8) + lionData  (8) +
   *         tiger1 VT (8) + tigerData (8) +
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
   *         animal  VT (8) + animalData  (8) + lionData (8)
   *         -------------------------
   *         * animal VT → (Points to lion VT: lion data can be used)
   *         -------------------------
   *           animal data
   *         -------------------------
   *           lion data
   *         -------------------------
   */
  std::cout << sizeof(lion1) << std::endl;
  /** \note: total 32bytes =
   *         animal  VT (8) + animalData  (8) + lion VT (8) + lionData (8)
   *         -------------------------
   *         * lion VT
   *         -------------------------
   *           lion data
   *         -------------------------
   *         * animal VT  → (Points to lion VT: lion data can be used..
   *                         BUT!! VT doesn't know where lion data is.
   *                         Therefore additional offset is needed to indicate their location in memory.
   *                         thunk function, des)
   *         -------------------------
   *           animal data
   *         -------------------------
   */
  std::cout << sizeof(lion2) << std::endl;

  animalInh *polyAnimal4 = new lion2();
  polyAnimal4->speak(); // call thunk function in lion VT!
  delete polyAnimal4;

  /** \remark: Figure for [Diamond inheritance VS Linear inheritance]
   * ------------------------------------------------------------------
   *       animal                * animal VT \ animal data
   *       /    \                  lion data
   *    lion    tiger            * animal VT \ animal data
   *       \    /                  tiger data
   *        liger                  liger data
   * ------------------------------------------------------------------
   *       animal                * lion VT \ lion data
   *       /    \ (virtual)      * tiger VT \ tiger data
   *    lion    tiger              liger data
   *       \    /                * animal VT \ animal data
   *        liger
   * ------------------------------------------------------------------
   */

  std::cout << "------------------------------------- [↑ Example 6 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [7] object slicing
   *    - object slicing is a phenomenon that occurs when an instance of a derived class is handled through a reference or pointer to the base class.
   *    - In this process, the member variables and methods of the derived class that are not defined in the base class get sliced off or ignored.
   *    - This can lead to data loss.
   *    - Object slicing can commonly occur when using polymorphism.
   *    - To avoid it, one must have a good understanding of the interaction between base and derived classes and be cautious when using pointers and references in an inheritance hierarchy.
   */

  doginh2 jim{1.0};
  // jim.speak();

  /** \note: No object slicing */
  animalInh2 &animalRef = jim;
  animalRef.speak();

  /** \note: Object slicing (From copy constructor, But VT is NOT copied!! → dogData is omiited)
   *         To aboid object slicing, delete copy constructor in base class
   *         → But, it cause compile error in the below case
   *         → Also, derived class is in error due to the deleted copy constructor! (It can be solved from copy constructor coved in protected)
   */
  // animal2 animalObj = jim;
  // animalObj.speak();

  doginh2 nim{jim};

  std::cout << "------------------------------------- [↑ Example 7-1 ↑] -------------------------------------" << std::endl;

  /** \example: The problem in case of operator overloading
   *     - Can be solved re-defined equality operator in child class
   */

  doginh2 kitty3{1.0};
  doginh2 nabi3{2.0};

  if (kitty3 == nabi3)
  {
    std::cout << "same!" << std::endl;
  }
  else
  {
    std::cout << "diff!" << std::endl;
  }

  std::cout << "------------------------------------- [↑ Example 7-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [8] Dynamic cast
   *    - Upcast:
   *        Upcasting is the process of converting a derived class reference or pointer to its base class reference or pointer.
   *        This process is generally safe and happens implicitly.
   *        When upcasting, the derived object is treated as an object of the base class, which means only the base class's members and methods are accessible.
   *        Any additional members or overridden methods from the derived class are ignored.
   *    - Downcast:
   *        Downcasting is the process of converting a base class reference or pointer to a derived class reference or pointer.
   *        Downcasting is generally not safe and must be done explicitly.
   *        This is because the compiler cannot guarantee that the base class object being downcasted is indeed an instance of the derived class.
   *        In C++, you can use dynamic_cast to safely perform a downcast, which returns a null pointer if the downcast is not valid.
   */

  catInh3 kitty;
  kitty.speak();

  // Prefer smart pointer!
  catInh3 *catPtr3 = new catInh3();

  /** \example: Upcast */
  /** \note: animalPtr cannot access to knead() */
  animalInh3 *animalUpPtr = catPtr3; // Same with static_cast<animalInh3 *>(catPtr3);
  animalUpPtr->speak();

  /** \example: Downcast */
  animalInh3 *animalDownPtr = new catInh3();
  // catPtr3 = animalDownPtr; // Downcast, Not allowed implicit downcast in c++
  // catPtr3 = static_cast<catInh3 *>(animalDownPtr); // VERY dangerous!!!!
  catInh3 *catPtr4 = dynamic_cast<catInh3 *>(animalDownPtr);
  if (catPtr4 == nullptr)
  {
    std::cout << "This is not a cat object" << std::endl;
    return;
  }
  catPtr4->speak();
  catPtr4->knead();
  delete animalDownPtr;

  std::cout << typeid(animalInh3).name() << std::endl;
  std::cout << typeid(catInh3).name() << std::endl;
  std::cout << typeid(dogInh3).name() << std::endl;

  /** \remark: RTTI
   * RTTI (Runtime Type Information) in C++ is a feature that provides information about the data type of an object at runtime.
   * This feature is essential to implement polymorphism in C++
   * RTTI is provided by the typeinfo header file, and it can be used through the typeid operator.
   * The typeid operator returns a type_info object that represents the data type of the object or expression passed as an argument.
   * RTTI is very useful when implementing polymorphism, which allows a parent class pointer or reference to handle child class objects.
   * With RTTI, the actual data type of the child class object pointed to by a parent class pointer can be checked at runtime, enabling correct polymorphism.
   * However, using RTTI can be a performance burden because code that uses RTTI information is generally slower to execute than code that is checked at compile time.
   */

  catPtr3->speak();
  delete catPtr3;

  std::cout << "------------------------------------- [↑ Example 8 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [9] I/O inheritance
   */

  catInh4 kitty4{"kitty", 3};
  catInh4 nabi4{"nabi", 2};

  kitty4.print(std::cout);
  nabi4.print(std::cout);

  {
    std::ofstream ofs("test.txt");
    if (!ofs)
    {
      std::cout << "Cannot open the file" << std::endl;
      return;
    }

    kitty4.print(ofs);
    nabi4.print(ofs);
  }

  std::stringstream ss;
  kitty4.print(ss);
  nabi4.print(ss);

  std::cout << ss.str() << std::flush;

  {
    std::ifstream inputFile("test.txt");
    if (!inputFile.is_open())
    {
      std::cout << "Cannot open the file" << std::endl;
      return;
    }

    catInh4 kitty5("", 0);
    std::string line("Not empty");
    while (1)
    {
      std::getline(inputFile, line);
      if (line.empty())
        break;
      std::istringstream is(line);
      kitty5.setFromStream(is);
      kitty5.print(std::cout);
    }
  }

  std::cout << "------------------------------------- [↑ Example 9 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
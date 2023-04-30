#include "ctemplate.h"

std::string demangle(const char *mangled_name)
{
  int status = 0;
  char *demangled = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status);

  std::string result;
  if (status == 0)
  {
    result = demangled;
    std::free(demangled);
  }
  else
  {
    result = mangled_name;
  }

  return result;
}

template <typename T>
void printVar(T a)
{
  std::cout << demangle(typeid(a).name()) << ", ";
  if constexpr (std::is_same_v<T, const char *>)
  {
    std::cout << static_cast<const char *>(a) << std::endl;
  }
  else
  {
    std::cout << a << std::endl;
  }
}

template <typename T>
void printVar_LRef(T &a)
{
  std::cout << demangle(typeid(a).name()) << ", ";
  if constexpr (std::is_same_v<T, const char *>)
  {
    std::cout << static_cast<const char *>(a) << std::endl;
  }
  else
  {
    std::cout << a << std::endl;
  }
}

template <typename T>
void printVar_RRef1(T &&a) // forward reference (universal reference: Both (L-value and R-value) are ok)
{
  std::cout << demangle(typeid(a).name()) << ", ";
  if constexpr (std::is_same_v<T, const char *>)
  {
    std::cout << static_cast<const char *>(a) << std::endl;
  }
  else
  {
    std::cout << a << std::endl;
  }

  if constexpr (std::is_same_v<std::decay_t<T>, std::string>)
  {
    std::string localVar{std::move(a)};
    std::cout << localVar << std::endl;
  }
}

template <typename T>
void printVar_RRef2(T &&a) // forward reference (universal reference: Both (L-value and R-value) are ok)
{
  std::cout << demangle(typeid(a).name()) << ", ";
  if constexpr (std::is_same_v<T, const char *>)
  {
    std::cout << static_cast<const char *>(a) << std::endl;
  }
  else
  {
    std::cout << a << std::endl;
  }

  if constexpr (std::is_same_v<std::decay_t<T>, std::string>)
  {
    /** \brief: std::forward
     *   - Forwards lvalues as either lvalues or as rvalues, depending on T
     *      a. For example, if used in a wrapper such as the following, the template behaves as described below:
     *
     *        template<class T>
     *        void wrapper(T&& arg)
     *        {
     *          // arg is always lvalue
     *          foo(std::forward<T>(arg)); // Forward as lvalue or as rvalue, depending on T
     *        }
     *
     *      * If a call to wrapper() passes an rvalue std::string, then T is deduced to std::string (not std::string&, const std::string&, or std::string&&), and std::forward ensures that an rvalue reference is passed to foo.
     *      * If a call to wrapper() passes a const lvalue std::string, then T is deduced to const std::string&, and std::forward ensures that a const lvalue reference is passed to foo.
     *      * If a call to wrapper() passes a non-const lvalue std::string, then T is deduced to std::string&, and std::forward ensures that a non-const lvalue reference is passed to foo.
     */

    std::string localVar{std::forward<T>(a)};
    std::cout << localVar << std::endl;
  }
}

void template_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] template introduction
   *    - Function template: For function overloading
   *    - Class template
   *    - Alias template
   *    - Variable template
   *    - (c++20) concept
   */

  int maxI = std::max<int>(1, 5);
  float maxF = std::max<float>(1.2f, 2.5f);
  double maxD = std::max<double>(1.4, 3.4);

  std::cout << maxI << std::endl;
  std::cout << maxF << std::endl;
  std::cout << maxD << std::endl;

  std::cout << "------------------------------------- [↑ Example 1-1 ↑] -------------------------------------" << std::endl;

  /** \example: Implicit template instantiation */
  int sumI = addFunc<int>(1, 1);
  double sumD = addFunc<double>(2.5, 5.1);
  // auto c = addFunc<auto>("abc", "def"); // COMPILE ERROR!

  std::cout << sumI << std::endl;
  std::cout << sumD << std::endl;

  std::cout << "------------------------------------- [↑ Example 1-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2] template type deduction, Perfect forwarding (std::forward())
   */

  auto at1 = 1;
  std::cout << at1 << ", ";
  std::cout << typeid(at1).name() << ", ";
  std::cout << demangle(typeid(at1).name()) << ", "; // OR ./program | c++filt -t in terminal
  printVar<double>(at1);

  auto at2 = 1.1;
  std::cout << at2 << ", ";
  std::cout << typeid(at2).name() << ", ";
  std::cout << demangle(typeid(at2).name()) << ", ";
  printVar<int>(at2);

  auto at3 = 1.2f;
  std::cout << at3 << ", ";
  std::cout << typeid(at3).name() << ", ";
  std::cout << demangle(typeid(at3).name()) << ", ";
  printVar<double>(at3);

  auto at4 = "Dongjae";
  std::cout << at4 << ", ";
  std::cout << typeid(at4).name() << ", ";
  std::cout << demangle(typeid(at4).name()) << ", ";
  printVar<std::string>(at4);

  std::cout << "------------------------------------- [↑ Example 2-1 ↑] -------------------------------------" << std::endl;

  printVar_LRef(at1);
  // printVar_LRef(std::move(at1)); // COMPILE ERROR!
  printVar_RRef1(at1 /** \var: L-Value */);            // T = string&, (string&)
  printVar_RRef1(std::move(at1) /** \var: R-Value */); // T = string, (string&&)

  std::cout << "------------------------------------- [↑ Example 2-2 ↑] -------------------------------------" << std::endl;

  std::string as1 = "Dongjae";
  printVar_RRef1(as1);
  printVar_RRef1(std::move(as1));
  std::string as2 = "Yoonkyung";
  printVar_RRef2(as2);
  printVar_RRef2(std::move(as2));
  std::cout << as2 << std::endl;

  std::cout << "------------------------------------- [↑ Example 2-3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] template instantiation
   *    - Multiple type parameters
   *    - Non-type parameter
   *    - Parameter pack
   *    - Template build (Instantiation)
   */

  /** \example: Multiple type parameters */
  // find(); //

  std::cout << "------------------------------------- [↑ Example 3-1 ↑] -------------------------------------" << std::endl;

  /** \example: Non-type parameter (Example: std::array) */

  std::cout << nontype_mul<double, 4>(2.0) << std::endl;
  std::cout << nontype_mul<double, 5>(2.0) << std::endl;

  std::cout << "------------------------------------- [↑ Example 3-2 ↑] -------------------------------------" << std::endl;

  /** \example: Parameter pack (Since c++17) */

  pack_print(1, 2, 3);
  pack_print("abc", "def", "ghi");

  std::cout << "------------------------------------- [↑ Example 3-3 ↑] -------------------------------------" << std::endl;

  std::cout << foo<int>(1) << std::endl;
  // std::cout << foo<double>(1.3) << std::endl; // COMPILE ERROR! (Not instantiation for <double>)

  std::cout << "------------------------------------- [↑ Example 3-4 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [4] template instantiation
   *    - Class template
   *    - Aliasing template
   *    - Variable template
   */

  /** \example: Class template */
  stack<int> stackData;
  stackData.push(1);
  stackData.push(2);
  stackData.push(3);

  int n;
  while (stackData.pop(n))
  {
    std::cout << n << std::endl;
  }

  std::cout << "------------------------------------- [↑ Example 4-1 ↑] -------------------------------------" << std::endl;

  /** \example: Aliasing template */

  using dongjaeInt = int; // alias
  dongjaeInt a{10};
  std::cout << a << std::endl;

  dongjaeKeys<float> floatKeys;   // std::vector<std::array<float, 64>>;
  dongjaeKeys<double> doubleKeys; // std::vector<std::array<double, 64>>;

  std::cout << "------------------------------------- [↑ Example 4-2 ↑] -------------------------------------" << std::endl;

  /** \example: Variable template (Since c++14) */

  int intPi = pi<int>;
  float floatPi = pi<float>;
  double doublePi = pi<double>;

  std::cout << intPi << std::endl;
  std::cout << floatPi << std::endl;
  std::cout << doublePi << std::endl;

  std::cout << "------------------------------------- [↑ Example 4-3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [5] template concept (Since c++20)
   *    - The concepts library provides definitions of fundamental library concepts that can be used to perform compile-time validation of template arguments and perform function dispatch based on properties of types. 
   *    - These concepts provide a foundation for equational reasoning in programs
   */

  std::cout << sum1<int>(10, 10) << std::endl;
  std::cout << sum1<uint64_t>(30, 40) << std::endl;
  std::cout << sum1<double>(1.5, 2.4) << std::endl;
  std::cout << sum2<std::string>("abc", "def") << std::endl; // COMPILE ERROR with addable1 concept! 

  std::cout << "------------------------------------- [↑ Example 5 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}

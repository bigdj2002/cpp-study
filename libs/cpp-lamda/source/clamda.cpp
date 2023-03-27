#include "clamda.h"

static void freeFunction(int i)
{
  std::cout << "freeFunction " << i << std::endl;
}

void runFunction(int i, const std::function<void(int)> &fn)
{
  fn(i);
}

void runFunctions(const std::vector<std::function<void(int)>> &functions)
{
  int i = 0;
  for (const auto &fn : functions)
  {
    fn(++i);
  }
}

int lamda_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] Lamda expression
   * \details: Constructs a closure: annamed function object capable of captuning variables in scope
   *           [ captures ] <tparams> ( params ) specifiers exception attr -> ret { body }
   *           [ captures ] ( params ) -> ret { body }
   *           [ captures ] ( params ) { body } *** More popular
   *           [ captures ] { body }
   *           [ captures ] → capture by 1)value, 2)reference, and 3)this
   */

  // Lamda expression is same with function object in assembly code
  int three{3};
  int *ptr = &three;
  auto lamdaPlus3 = [localVar = 3, three, &ptr](int x)
  {
    return localVar + three + ptr[0] + x;
  };

  plus plus3{3};
  plus plus5{5};

  std::cout << plus3(10) << std::endl;
  std::cout << plus5(10) << std::endl;
  std::cout << lamdaPlus3(10) << std::endl;
  std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2] Lamda capture [ this ]
   * \details:
   */

  cat1 kitty{1};
  kitty.test();

  std::vector<int> nums1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  auto lamdaAdd10 = [](int &n)
  {
    n += 10;
  };

  int n = 10;
  lamdaAdd10(n);
  std::cout << n << std::endl;

  // example 1)
  std::for_each(nums1.begin(), nums1.end(), lamdaAdd10);
  // example 2)
  std::for_each(nums1.begin(), nums1.end(), [](int &n)
                { n += 10; });

  for (int num : nums1)
  {
    std::cout << num << " ";
  }
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] Higher order functions
   * \details:
   *  1. takes one or more functions as arguments (i.e. a procedural parameter, which is a parameter of a procedure that is itself a procedure)
   *  2. returns a function as its result.
   *  → Example library: erase, remove_if, sort, reduce
   */

  std::vector<int> nums2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> nums3{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> nums4{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  [[maybe_unused]] auto filterOdd = [](int n)
  { return n % 2 == 1; };

  nums2.erase(std::remove_if(nums2.begin(), nums2.end(), [](int n)
                             { return n % 2 == 1; }),
              nums2.end());
  // nums2.erase(std::remove_if(nums2.begin(), nums2.end(), filterOdd), nums2.end()); // Same with above codes

  for (int num : nums2)
  {
    std::cout << num << " ";
  }
  std::cout << std::endl;

  std::sort(nums3.begin(), nums3.end(), [](int a, int b)
            {
        // return a > b;
        return std::abs(a-5) < std::abs(b-5); });

  for (int num : nums3)
  {
    std::cout << num << " ";
  }
  std::cout << std::endl;

  // int sum = std::reduce(nums4.begin(), nums4.end(), 0, [](int a, int b)
  //                       { return a + b; }); // Supported since C++ 17
  // std::cout << sum << std::endl;
  // Similar with std::accumulate

  cat1 cata{10}, catb{11}, catc{13}, catd{16};
  std::vector<cat1> cats;
  cats.push_back(cata);
  cats.push_back(catb);
  cats.push_back(catc);
  cats.push_back(catd);

  std::sort(cats.begin(), cats.end(), [](cat1 &a, cat1 &b)
            { return a.age() > b.age(); });
  for (cat1 &cat : cats)
  {
    std::cout << cat.age() << " ";
  }
  std::cout << std::endl;

  std::cout << "------------------------------------- [↑ Example 3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [4] std::function (Delivery function, functional programming)
   * \details:
   *   1. Class template std::function is a general-purpose polymorphic function wrapper.
   *      Instances of std::function can store, copy, and invoke any CopyConstructible Callable target -- functions (via pointers thereto),
   *      lambda expressions, bind expressions, or other function objects, as well as pointers to member functions and pointers to data members.
   *   2. The stored callable object is called the target of std::function.
   *      If a std::function contains no target, it is called empty.
   *      Invoking the target of an empty std::function results in std::bad_function_call exception being thrown.
   */

  freeFunction(10);
  void (*fnPtr)(int);
  fnPtr = freeFunction;
  (*fnPtr)(20);
  runFunction(30, fnPtr);

  FunctionObj functionObj;
  functionObj(10);
  runFunction(30, functionObj);

  auto lamdaFn = [](int i)
  {
    std::cout << "lamdaFunction " << i << std::endl;
  };
  lamdaFn(10);
  runFunction(30, lamdaFn);

  std::vector<std::function<void(int)>> functions;
  functions.emplace_back(freeFunction);
  functions.emplace_back(functionObj);
  functions.emplace_back(lamdaFn);
  runFunctions(functions);

  std::cout << "------------------------------------- [↑ Example 4 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  return 0;
}
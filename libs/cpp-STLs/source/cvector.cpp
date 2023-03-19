#include "cvector.h"

#if PARALLEL
#include <execution>
#define SEQ std::execution::seq,
#define PAR std::execution::par,
#else
#define SEQ
#define PAR
#endif

bool operator<(const Employee &lhs, const Employee &rhs)
{
  return lhs.age < rhs.age;
}

void printVec(const std::vector<int> &vec)
{
  std::cout << "v= {";
  for (int i : vec)
    std::cout << i << ", ";
  std::cout << "}\n";
}

int vector_example()
{
  int *numsPtr = new int[5];
  for (int i = 0; i < 5; i++)
    numsPtr[i] = i;
  delete numsPtr;




  /**
   * \brief: [1] std::vector - basic level
   */

  /** \example: #1 */
  std::vector<int> nums1(10);
  for (int i = 0; i < 10; i++)
    nums1[i] = i;
  std::cout << nums1.size() << std::endl;
  std::cout << "------------------------------------- [↑ Example 1-1 ↑] -------------------------------------" << std::endl;

  /** \example: #2 */
  std::vector<int> nums2{0, 1, 2, 3, 4};
  nums2.emplace_back(5);
  std::cout << nums2.size() << std::endl;
  nums2.pop_back();
  std::cout << nums2.size() << std::endl;
  std::cout << "------------------------------------- [↑ Example 1-2 ↑] -------------------------------------" <<std::endl;

  /** \example: #3 */
  for (std::size_t i = 0; i < nums2.size(); i++)
  {
    std::cout << nums2[i] << " ";
  }
  std::cout << std::endl;

  for (auto itr = nums2.begin(); itr != nums2.end(); itr++)
  {
    std::cout << *itr << " ";
  }
  std::cout << std::endl;

  for (const auto &itr : nums2)
  {
    std::cout << itr << " ";
  }
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 1-3 ↑] -------------------------------------" << std::endl;

  /** \example: #4 */
  std::vector<Cat1> cats1;
  cats1.emplace_back(Cat1(1));
  cats1.emplace_back(Cat1(2));
  cats1.emplace_back(Cat1(3));
  cats1.emplace_back(Cat1(4));
  cats1.emplace_back(Cat1(5));

  for (const auto &cat : cats1)
  {
    // std::cout << cat << " "; // Wrong!
    cat.speak1();
  }
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 1-4 ↑] -------------------------------------" << std::endl;




  /**
   * \brief: [2] std::vector - intermediate level
   */

  /** \example: #1 */
  std::vector<int> nums3(10000, 1);
  nums3.emplace_back(2);           // O(1)
  nums3.pop_back();                // O(1)
  nums3.emplace(nums3.begin(), 3); // O(N), N=10000 (Need to move next for all elements) -> only at first or last position
  nums3.erase(nums3.begin());      // O(N), N=10000 (Need to move next for all elements) -> only at first or last position
  std::cout << "------------------------------------- [↑ Example 2-1 ↑] -------------------------------------" << std::endl;

  /** \example: #2 */
  std::vector<Cat1> cats2;
  cats2.emplace_back(Cat1{"cat0", 0});
  cats2.emplace_back(Cat1{"cat1", 0});
  cats2.emplace_back(Cat1{"kitty", 2});
  cats2.emplace_back("kitty", 3); // Will not be generated temp memory to move
  for (const auto &cat : cats2)
  {
    cat.speak2();
  }
  std::cout << std::endl;

  Cat1 nabi{"nabi", 3};
  cats2.emplace_back(nabi);            // L-Value : copy
  cats2.emplace_back(std::move(nabi)); // R-Value : move
  std::cout << "------------------------------------- [↑ Example 2-2 ↑] -------------------------------------" << std::endl;




  /**
   * \brief: [3] std::vector - intermediate level (On memory issue)
   */

  /** \example: #1 */
  std::vector<int> nums4{1, 2, 3, 4, 5};
  std::cout << nums4.size() << " ";
  std::cout << nums4.capacity() << " " << std::endl;
  nums4.emplace_back(6);
  std::cout << nums4.size() << " ";
  std::cout << nums4.capacity() << " " << std::endl;
  for (std::size_t i = nums4.size(); i < 25; i++)
  {
    nums4.emplace_back(i+1);
    std::cout << nums4[i] << " ";
  }
  std::cout << std::endl;
  std::cout << nums4.size() << " ";           // Size: Num
  std::cout << nums4.capacity() << std::endl; // Capacity: retained memory by vector
  // Normarly capacity tries to retain temp memory wi th double size (5 - >10)
  // Need additional time to alloc extra memory (-> reserve)

  std::cout << sizeof(nums4) << std::endl; // Total byte(24) = Pointer(8) + size info(8) + capacity info(8)
  std::cout << "------------------------------------- [↑ Example 3-1 ↑] -------------------------------------" << std::endl;
  
  /** \example: #2 */
  std::vector<Cat2> cats3;  
  cats3.emplace_back("Kitty3");
  cats3.emplace_back("Nabi3"); // will happen mem copy (not mem`ove) -> unefficient.. it is reason to declare "noexcept" keyword

  std::vector<Cat2> cats4;
  cats4.reserve(2); // MORE CLEAN!
  cats4.emplace_back("Kitty4");
  cats4.emplace_back("Nabi4");
  std::cout << "------------------------------------- [↑ Example 3-2 ↑] -------------------------------------" << std::endl;




  /**
   * \brief: [4] std::vector - intermediate level (On for loop)
   */

  /** \example: #1 */
  std::size_t n = 10000;
  std::size_t l = 1000;
  std::vector<int> numsa(n, 1);
  std::vector<int> numsb(n, 1);
  std::vector<int> numsc(n, 1);

  // Index-based
  auto start1 = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < l; i++)
  {
    for (std::size_t idx = 0; idx < numsa.size(); idx++)
    {
      numsa[idx] *= 2;
    }
  }
  auto end1 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time1 = end1 - start1;
  std::cout << "Index-based loop: " << time1.count() << std::endl;

  // Iterator-based
  auto start2 = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < l; i++)
  {
    for (auto itr = numsb.begin(); itr != numsb.end(); itr++)
    {
      *itr *= 2;
    }
  }
  auto end2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time2 = end2 - start2;
    std::cout << "Iterator-based loop: " << time2.count() << std::endl;

  // Range-based (Safe and stable method)
  auto start3 = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < l; i++)
  {
    for (auto &num : numsc)
    {
      num *= 2;
    }
  }
  auto end3 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time3 = end3 - start3;
  std::cout << "Range-based loop: " << time3.count() << std::endl;
  std::cout << "------------------------------------- [↑ Example 4-1 ↑] -------------------------------------" << std::endl;

  /** \example: #2 - In case of coding in index-based loop  */
  std::vector<int> nums11{0, 1, 0, 1};
  std::vector<int> nums22{0, 1, 0, 1};
  std::vector<int> nums33{0, 1, 0, 1};

  for (size_t i = 0; i < nums11.size(); i++)
  {
    if (nums11[i] == 0)
      nums11.emplace_back(2); // If size of vector is changes, index-based loop must use!
  }

  for (auto itr = nums22.begin(); itr != nums22.end(); itr++)
  {
    if (*itr == 0)
      nums22.emplace_back(2); // Possible to copy & move whole vectors another address in memory due to push process! Therefore, itr points meaningless pos in memory
  }

  for (auto &num : nums33)
  {
    if (num == 0)
      nums33.emplace_back(2); // Possible to change capacity. 
  }

  for (const int n : nums11)
    std::cout << n << " ";
  std::cout << std::endl;

  for (const int n : nums22)
    std::cout << n << " ";
  std::cout << std::endl;

  for (const int n : nums33)
    std::cout << n << " ";
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 4-2 ↑] -------------------------------------" << std::endl;




  /**
   * \brief: [5] std::vector - intermediate level (On erase VS remove)
   * \details: std::remove, std::remove_if
   * Removes all elements satisfying specific criteria from the range [first, last) and returns a past-the-end iterator for the new end of the range.
   * Removing is done by shifting (by means of copy assignment (until C++11) move assignment (since C++11)) the elements in the range in such a way that the elements that are not to be removed appear in the beginning of the range. 
   */

  std::vector<int> nums111 = {0, 1, 0, 1, 0, 1, 0};
  std::vector<int> nums222 = {0, 1, 0, 1, 0, 1, 0};
  std::vector<int> nums333 = {0, 1, 2, 3, 4, 5, 6};
  std::vector<Cat1> cats111;

  /** \example: #1 */
  nums111.erase(std::remove(nums111.begin(), nums111.end(), 0), nums111.end());
  for (const int n : nums111)
    std::cout << n << " ";
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 5-1 ↑] -------------------------------------" << std::endl;

  /** \example: #2a */
  /** \details: std::remove process
   *             ↓(begin)                    ↓(end)
   * step 1. [   0   1   0   1   0   1   0   ]

   *             ↓   ↓                       ↓(end)
   * step 2. [   0   1   0   1   0   1   0   ] : Compare [0] VS [1]

   *             ↓   ↓                       ↓(end)
   * step 3. [   1   1   0   1   0   1   0   ] : Delete [0] and Move and Copy from [1] to [0]

   *                 ↓   ↓                   ↓(end)
   * step 4. [   1   1   0   1   0   1   0   ] : pointers are moved next

   *                 ↓       ↓               ↓(end)
   * step 5. [   1   1   0   1   0   1   0   ] : pointer move

   *                     ↓       ↓           ↓(end)
   * step 6. [   1   1   0   1   0   1   0   ] : 2nd pointer points [4] (value 0) So, move next

   *                     ↓                   ↓(end)
   * step 7. [   1   1   1   1   0   1   0   ] : Delete [5] and Move and Copy from [5] to [3]
   */
  auto itr = std::remove(nums222.begin(), nums222.end(), 0); // *** Very important ***
  for (const int n : nums222)
    std::cout << n << " ";
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 5-2a ↑] -------------------------------------" << std::endl;

  /** \example: #2b */
  nums222.erase(itr, nums222.end());
  for (const int n : nums222)
    std::cout << n << " ";
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 5-2b ↑] -------------------------------------" << std::endl;

  /** \example: #3 */
  nums333.erase(std::remove_if(nums333.begin(), nums333.end(), 
  [](int n){ if(n % 2 == 0) {return true;} return false; } // lamda function (can be set function pointer)
  ), nums333.end());
  for (const int n : nums333)
    std::cout << n << " ";
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 5-3 ↑] -------------------------------------" << std::endl;

  /** \example: #4 */
  cats111.emplace_back("cat1", 1);
  cats111.emplace_back("cat2", 2);
  cats111.emplace_back("cat3", 3);
  cats111.emplace_back("cat4", 4);
  cats111.erase(std::remove_if(cats111.begin(), cats111.end(), [](const Cat1 & cat){if(cat.age() % 2 == 0) {return true;} return false;}), cats111.end());
  for (const Cat1 & cat : cats111)
    cat.speak1();
  std::cout << std::endl << std::endl;
  std::cout << "------------------------------------- [↑ Example 5-4↑] -------------------------------------" << std::endl;




  /**
   * \brief: [6] std::vector - algorithm
   */

  /** \category: sorting */
  /** \example: #1a sort*/
  std::vector<int> datas{1,3,6,8,123,23,78,16,23,75,86,93,32};
  std::sort(datas.begin(), datas.end() /*, Callable object(ex. lamda function)*/);
  for(auto data : datas)
    std::cout << data << " ";
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 6-1a ↑] -------------------------------------" << std::endl;

  /** \example: #1b stable_sort in cppreference.com */
  std::vector<Employee> v1 =
      {
          {108, "Zaphod"},
          {32, "Arthur"},
          {108, "Ford"},
      };

  std::stable_sort(v1.begin(), v1.end());
  for (const Employee &e : v1)
    std::cout << e.age << ", " << e.name << '\n';
  std::cout << "------------------------------------- [↑ Example 6-1b ↑] -------------------------------------" << std::endl;

  /** \example: #1c partial_sort in cppreference.com */
  auto print = [](auto const &s, int middle)
  {
    for (int a : s)
      std::cout << a << ' ';
    std::cout << '\n';
    if (middle > 0)
    {
      while (middle-- > 0)
        std::cout << "──";
      std::cout << '^';
    }
    else if (middle < 0)
    {
      for (auto i = s.size() + middle; --i; std::cout << "  ")
      {
      }

      for (std::cout << '^'; middle++ < 0; std::cout << "──")
      {
      }
    }
    std::cout << '\n';
  };

  std::array<int, 10> s1{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
  print(s1, 0);
  std::partial_sort(s1.begin(), s1.begin() + 3, s1.end());
  print(s1, 3);
  std::partial_sort(s1.rbegin(), s1.rbegin() + 4, s1.rend());
  print(s1, -4);
  std::partial_sort(s1.rbegin(), s1.rbegin() + 5, s1.rend(), std::greater{});
  print(s1, -5);
  std::cout << "------------------------------------- [↑ Example 6-1c ↑] -------------------------------------" << std::endl;

  /** \example: #1d nth_element in cppreference.com */
  std::vector<int> v2{5, 10, 6, 4, 3, 2, 6, 7, 9, 3};
  printVec(v2);

  auto m = v2.begin() + v2.size() / 2;
  std::nth_element(v2.begin(), m, v2.end());
  std::cout << "\nThe median is " << v2[v2.size() / 2] << '\n';
  // The consequence of the inequality of elements before/after the Nth one:
  assert(std::accumulate(v2.begin(), m, 0) < std::accumulate(m, v2.end(), 0));
  printVec(v2);

  // Note: comp function changed
  std::nth_element(v2.begin(), v2.begin() + 1, v2.end(), std::greater{});
  std::cout << "\nThe second largest element is " << v2[1] << '\n';
  std::cout << "The largest element is " << v2[0] << '\n';
  printVec(v2);
  std::cout << "------------------------------------- [↑ Example 6-1d ↑] -------------------------------------" << std::endl;

  /** \category: min/max */
  /** \example: #2a min_element in cppreference.com */
  std::vector<int> v3{3, 1, 4, 1, 5, 9};
  std::vector<int>::iterator result = std::min_element(v3.begin(), v3.end());
  std::cout << "min element at: " << std::distance(v3.begin(), result) << std::endl;
  std::cout << "------------------------------------- [↑ Example 6-2a ↑] -------------------------------------" << std::endl;

  /** \example: #2b max_element in cppreference.com */
  std::vector<int> v4{3, 1, -14, 1, 5, 9};
  // std::vector<int>::iterator result;

  result = std::max_element(v4.begin(), v4.end());
  std::cout << "max element found at index "
            << std::distance(v4.begin(), result)
            << " has value " << *result << '\n';

  result = std::max_element(v4.begin(), v4.end(), [](int a, int b)
                            { return std::abs(a) < std::abs(b); });
  std::cout << "absolute max element found at index "
            << std::distance(v4.begin(), result)
            << " has value " << *result << '\n';
  std::cout << "------------------------------------- [↑ Example 6-2b ↑] -------------------------------------" << std::endl;

  /** \example: #2c minmax_element in cppreference.com */
  const auto v5 = {3, 9, 1, 4, 2, 5, 9};
  const auto [min, max] = std::minmax_element(begin(v5), end(v5));

  std::cout << "min = " << *min << ", max = " << *max << '\n';
  std::cout << "------------------------------------- [↑ Example 6-2c ↑] -------------------------------------" << std::endl;

  /** \category: find */
  /** \example: #3a find/find_if in cppreference.com */
  std::vector<int> v6{1, 2, 3, 4};
  int n1 = 3;
  int n2 = 5;
  auto is_even = [](int i)
  { return i % 2 == 0; };

  auto result1 = std::find(std::begin(v6), std::end(v6), n1);
  auto result2 = std::find(std::begin(v6), std::end(v6), n2);
  auto result3 = std::find_if(std::begin(v6), std::end(v6), is_even);

  (result1 != std::end(v6))
      ? std::cout << "v contains " << n1 << '\n'
      : std::cout << "v does not contain " << n1 << '\n';

  (result2 != std::end(v6))
      ? std::cout << "v contains " << n2 << '\n'
      : std::cout << "v does not contain " << n2 << '\n';

  (result3 != std::end(v6))
      ? std::cout << "v contains an even number: " << *result3 << '\n'
      : std::cout << "v does not contain even numbers\n";
  std::cout << "------------------------------------- [↑ Example 6-3a ↑] -------------------------------------" << std::endl;

  /** \example: #3b binary_search in cppreference.com */
  std::vector<int> haystack{1, 3, 4, 5, 9};
  std::vector<int> needles{1, 2, 3};

  for (auto needle : needles)
  {
    std::cout << "Searching for " << needle << '\n';
    if (std::binary_search(haystack.begin(), haystack.end(), needle))
      std::cout << "Found " << needle << '\n';
    else
      std::cout << "no dice!\n";
  }
  std::cout << "------------------------------------- [↑ Example 6-3b ↑] -------------------------------------" << std::endl;

  /** \category: reduce */
  /** \example: #4a accumulate in cppreference.com */
  std::vector<int> v7{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  int sum = std::accumulate(v7.begin(), v7.end(), 0);
  int product = std::accumulate(v7.begin(), v7.end(), 1, std::multiplies<int>());

  auto dash_fold = [](std::string a, int b)
  {
    return std::move(a) + '-' + std::to_string(b);
  };

  std::string s = std::accumulate(std::next(v7.begin()), v7.end(),
                                  std::to_string(v7[0]), // start with first element
                                  dash_fold);

  // Right fold using reverse iterators
  std::string rs = std::accumulate(std::next(v7.rbegin()), v7.rend(),
                                   std::to_string(v7.back()), // start with last element
                                   dash_fold);

  std::cout << "sum: " << sum << '\n'
            << "product: " << product << '\n'
            << "dash-separated string: " << s << '\n'
            << "dash-separated string (right-folded): " << rs << '\n';
  std::cout << "------------------------------------- [↑ Example 6-4a ↑] -------------------------------------" << std::endl;

  /** \example: #4b reduce in cppreference.com */
  // std::cout.imbue(std::locale("en_US.UTF-8"));
  std::cout << std::fixed << std::setprecision(1);
  auto eval = [](auto fun)
  {
    const auto t1 = std::chrono::high_resolution_clock::now();
    const auto [name, result] = fun();
    const auto t2 = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> ms = t2 - t1;
    std::cout << std::setw(28) << std::left << name << "sum: "
              << result << "\t time: " << ms.count() << " ms\n";
  };
  {
    const std::vector<double> v(100'000'007, 0.1);

    eval([&v]
         { return std::pair{"std::accumulate (double)",
                            std::accumulate(v.cbegin(), v.cend(), 0.0)}; });
    eval([&v]
         { return std::pair{"std::reduce (seq, double)",
                            std::reduce(SEQ v.cbegin(), v.cend())}; });
    eval([&v]
         { return std::pair{"std::reduce (par, double)",
                            std::reduce(PAR v.cbegin(), v.cend())}; });
  }
  {
    const std::vector<long> v(100'000'007, 1);

    eval([&v]
         { return std::pair{"std::accumulate (long)",
                            std::accumulate(v.cbegin(), v.cend(), 0l)}; });
    eval([&v]
         { return std::pair{"std::reduce (seq, long)",
                            std::reduce(SEQ v.cbegin(), v.cend())}; });
    eval([&v]
         { return std::pair{"std::reduce (par, long)",
                            std::reduce(PAR v.cbegin(), v.cend())}; });
  }
  std::cout << "------------------------------------- [↑ Example 6-4b ↑] -------------------------------------" << std::endl;

  std::cout << std::endl;
  return 0;
}
#include "cset.h"

struct customFn1
{
  bool operator()(const int lhs, const int rhs) const
  {
    return lhs > rhs;
  }
};

struct customFn2
{
  bool operator()(const int lhs, const int rhs) const
  {
    return (lhs % 10) < (rhs % 10);
  }
};

bool operator<(const cat_set &lhs, const cat_set &rhs)
{
  if (lhs.age() == rhs.age())
    return lhs.name() < rhs.name();
  else
    return lhs.age() < rhs.age();
}

void set_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */
  /**
   * \brief: [1] std::set
   * \details:
   *    - std::set is an associative container that contains a sorted set of unique objects of type Key.
   *    - Sorting is done using the key comparison function Compare.
   *    - Search, removal, and insertion operations have logarithmic complexity.
   *    - Sets are usually implemented as red-black trees.
   */

  std::set<int> nums1{1, 3, 2, 4, 5};           // Stord in the way (red-black tree → Binary search tree)
  std::set<int, customFn1> nums2{1, 3, 2, 4, 5}; // Customized rule
  std::set<int, customFn2> nums3{1, 3, 2, 4, 5}; // Customized rule
  nums1.emplace(3);
  nums1.emplace(6);
  nums1.emplace(-500);
  nums1.emplace(5000);
  for (const int num : nums1)
  {
    std::cout << num << " ";
  }
  std::cout << std::endl;
  for (const int num : nums2)
  {
    std::cout << num << " ";
  }
  std::cout << std::endl;

  nums3.emplace(11);
  nums3.emplace(21);
  nums3.emplace(101);
  for (const int num : nums3)
  {
    std::cout << num << " ";
  }

  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 1-1 ↑] -------------------------------------" << std::endl;

  std::set<cat_set> cats;
  cats.emplace(1, "nabi");
  cats.emplace(2, "kitty");
  cats.emplace(1, "wal");

  for (const auto &cat : cats)
  {
    cat.speak();
  }
  std::cout << "------------------------------------- [↑ Example 1-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2] std::mutliset
   * \details:
   *    - std::multiset is an associative container that contains a sorted set of objects of type Key.
   *    - Unlike set, multiple keys with equivalent values are allowed.
   *    - Sorting is done using the key comparison function Compare.
   *    - Search, insertion, and removal operations have logarithmic complexity.
   */

  std::multiset<int> nums4{1, 3, 3, 3, 3, 2, 4, 5};
  for (const int num : nums4)
  {
    std::cout << num << " ";
  }
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
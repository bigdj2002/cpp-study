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

struct catHash
{
    std::size_t operator()(cat_set const& s) const noexcept
    {
        std::size_t h1 = std::hash<int>{}(s.age());
        std::size_t h2 = std::hash<std::string>{}(s.name());
        return h1 ^ h2; // or use boost::hash_combine
    }
};

namespace std
{
    template <>
    struct hash<cat_set>
    {
        std::size_t operator()(cat_set const &s) const noexcept
        {
          std::size_t h1 = std::hash<int>{}(s.age());
          std::size_t h2 = std::hash<std::string>{}(s.name());
          return h1 ^ h2 ; // or use boost::hash_combine
        }
    };
}

bool operator==(const cat_set &lhs, const cat_set &rhs) noexcept
{
    return (lhs.age() == rhs.age()) && (lhs.name() == rhs.name());
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

  std::set<int> nums1{1, 3, 2, 4, 5};            // Stord in the way (red-black tree → Binary search tree)
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

  /**
   * \brief: [2] std::unordered_set
   * \details:
   *    - Unordered set is an associative container that contains a set of unique objects of type Key. 
   *    - Search, insertion, and removal have average constant-time complexity.
   *    - Internally, the elements are not sorted in any particular order, but organized into buckets. 
   *    - Which bucket an element is placed into depends entirely on the hash of its value. 
   *    - This allows fast access to individual elements, since once a hash is computed, it refers to the exact bucket the element is placed into.
   *    - Container elements may not be modified (even by non const iterators) since modification could change an element's hash and corrupt the container.
   */

  std::unordered_set<std::string> uordSet;
  uordSet.reserve(100); // To prevent re-hashing
  std::cout << "load_factor: " << uordSet.load_factor() << std::endl;

  uordSet.emplace("abc");
  uordSet.emplace("def");
  uordSet.emplace("ghi");
  uordSet.emplace("jkl");

  std::cout << "buchet count: " << uordSet.bucket_count() << std::endl;
  for (const auto & str : uordSet)
  {
    std::cout << str << std::endl;
    std::cout << str << " hash: " << std::hash<std::string>{}(str) << ", bucket: " << uordSet.bucket(str) << std::endl;
  }
  std::cout << "------------------------------------- [↑ Example 2-1 ↑] -------------------------------------" << std::endl;

  uordSet.find("abc"); // O(1)
  uordSet.insert("lmn"); // O(1)
  uordSet.erase("def"); // O(1)
  for (const auto &str : uordSet)
  {
    std::cout << str << std::endl;
  }
  std::cout << "------------------------------------- [↑ Example 2-2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] hash set / std::unordered_set
   * \details:
   */

  cat_set kitto{1, "kitto"};
  cat_set nabu{2, "nabu"};

  std::unordered_set<cat_set, catHash> cats1;
  std::unordered_multiset<cat_set> cats2;
  cats1.emplace(kitto);
  cats1.emplace(nabu);
  cats1.emplace(1, "kitto");
  cats2.emplace(kitto);
  cats2.emplace(nabu);
  cats2.emplace(1, "kitto");

  for (const auto &cat : cats1)
  {
    cat.speak();
  }
   for (const auto &cat : cats2)
  {
    cat.speak();
  }
  std::cout << "------------------------------------- [↑ Example 3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
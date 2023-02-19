#include "cvector.h"

int vector_example()
{
  int *numsPtr = new int[5];
  for (int i = 0; i < 5; i++)
    numsPtr[i] = i;
  delete numsPtr;

  /* ----------------------------------------------------- */

  std::vector<int> nums1(10);
  for (int i = 0; i < 10; i++)
    nums1[i] = i;
  std::cout << nums1.size() << std::endl;
  std::cout << std::endl;

  /* ----------------------------------------------------- */

  std::vector<int> nums2{0, 1, 2, 3, 4};
  nums2.emplace_back(5);
  std::cout << nums2.size() << std::endl;
  nums2.pop_back();
  std::cout << nums2.size() << std::endl;
  std::cout << std::endl;

  /* ----------------------------------------------------- */

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
  std::cout << std::endl
            << std::endl;

  /* ----------------------------------------------------- */

  std::vector<Cat> cats1;
  cats1.emplace_back(Cat(1));
  cats1.emplace_back(Cat(2));
  cats1.emplace_back(Cat(3));
  cats1.emplace_back(Cat(4));
  cats1.emplace_back(Cat(5));

  for (const auto &cat : cats1)
  {
    // std::cout << cat << " "; // Wrong!
    cat.speak1();
  }
  std::cout << std::endl
            << std::endl;

  /* ----------------------------------------------------- */

  std::vector<int> nums3(10000, 1);
  nums3.emplace_back(2);           // O(1)
  nums3.pop_back();                // O(1)
  nums3.emplace(nums3.begin(), 3); // O(N), N=10000 (Need to move next for all elements) -> only at first or last position
  nums3.erase(nums3.begin());      // O(N), N=10000 (Need to move next for all elements) -> only at first or last position

  /* ----------------------------------------------------- */

  std::vector<Cat> cats2;
  cats2.emplace_back(Cat{"cat0", 0});
  cats2.emplace_back(Cat{"cat1", 0});
  cats2.emplace_back(Cat{"kitty", 2});
  cats2.emplace_back("kitty", 3); // Will not be generated temp memory to move
  for (const auto &cat : cats2)
  {
    cat.speak2();
  }
  std::cout << std::endl
            << std::endl;

  Cat nabi{"nabi", 3};
  cats2.emplace_back(nabi);            // L-Value : copy
  cats2.emplace_back(std::move(nabi)); // R-Value : move

  /* ----------------------------------------------------- */

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
  std::cout << std::endl;
  
  /* ----------------------------------------------------- */

  std::vector<Cat2> cats3;  
  cats3.emplace_back("Kitty3");
  cats3.emplace_back("Nabi3"); // will happen mem copy (not mem move) -> unefficient.. it is reason to declare "noexcept" keyword

  std::vector<Cat2> cats4;
  cats4.reserve(2); // MORE CLEAN!
  cats4.emplace_back("Kitty4");
  cats4.emplace_back("Nabi4");

  return 0;
}
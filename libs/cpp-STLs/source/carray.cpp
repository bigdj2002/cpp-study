#include "carray.h"

void fnarray()
{
    std::array<int, 100> nums;
    nums.fill(0);
    for (const int n : nums)
    {        
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

void fnvector()
{
    std::vector<int> nums(100);
    nums.reserve(1000);
}

void array_example()
{
    fnarray();
    fnvector();

    /**
     * \brief: Array VS Vector
     * common: sequential memory (Supports random access)
     * Array:  Stack / Compile time / fixed size     / limited to stack size
     * Vector: Heap  / Runtime      / variable size  / huge memory size
    */
}
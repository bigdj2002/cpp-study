#include "q_0945.h"

void leet_test_0945()
{
    Solution_0945 sol;

    std::vector<int> nums = {3, 2, 1, 2, 1, 7};
    // std::vector<int> nums = {1,2,2};

    int num = sol.minIncrementForUnique(nums);

    printf("%d", num);
    printf("\n");
}
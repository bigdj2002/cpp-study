#include "q_0773.h"

void leet_test_0773()
{
    Solution_0773 sol;

    // std::vector<std::vector<int>> nums = {{1, 2, 3}, {4, 0, 5}};
    std::vector<std::vector<int>> nums = {{4, 1, 2}, {5, 0, 3}};

    int num = sol.slidingPuzzle(nums);

    printf("%d", num);
    printf("\n");
}
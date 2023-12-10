#include "q_0001.h"

void leet_test_0001()
{
    Solution_0001 sol;

    std::vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    std::vector<int> answer;
    answer = sol.twoSum(nums, target);

    for (unsigned i = 0; i < answer.size(); ++i)
    {
        printf("%d ", answer[i]);
    }
    printf("\n");
}
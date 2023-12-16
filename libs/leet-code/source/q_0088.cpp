#include "q_0088.h"

void leet_test_0088()
{
    Solution_0088 sol;

    int m = 3;
    std::vector<int> nums1 = {1, 2, 3, 0, 0, 0};

    int n = 3;
    std::vector<int> nums2 = {1, 5, 6};

    sol.merge(nums1, m, nums2, n);

    for (unsigned i = 0; i < nums1.size(); ++i)
    {
        printf("%d ", nums1[i]);
    }
    printf("\n");
}
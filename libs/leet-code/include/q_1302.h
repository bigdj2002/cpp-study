#include "test_base.h"

/**
 * \name: Deepest Leaves Sum [Medium]
 */

// Given the root of a binary tree, return the sum of values of its deepest leaves.

// Example 1:
//              1
//           ↙    ↘
//           2     3
//         ↙  ↘     ↘
//        4    5     6
//       ↙            ↘
//      7              8
// Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
// Output: 15

// Example 2:
//               6
//            ↙    ↘
//           7      8
//         ↙  ↘   ↙  ↘
//        2    7  1    3
//      ↙    ↙  ↘      ↘
//     9     1   4       5
// Input: root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
// Output: 19

// Constraints:
// The number of nodes in the tree is in the range [1, 104].
// 1 <= Node.val <= 100

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution_1302
{
    using T = std::vector<std::vector<int>>;

public:
    void travel_in_post_order(TreeNode *node, int depth, T &vec)
    {
        if (node == nullptr)
            return;

        if (vec.size() <= (size_t)depth)
            vec.push_back({});

        vec[depth].push_back(node->val);

        if (node->left != nullptr)
            travel_in_post_order(node->left, depth + 1, vec);
        if (node->right != nullptr)
            travel_in_post_order(node->right, depth + 1, vec);
    }

    int deepestLeavesSum(TreeNode *root)
    {
        std::vector<std::vector<int>> vals;
        travel_in_post_order(root, 0, vals);
        int last_depth = vals.size() - 1;
        int num_element = vals[last_depth].size();
        int sum = 0;
        for (int i = 0; i < num_element; i++)
            sum += vals[last_depth][i];
        return sum;
    }
};

void leet_test_1302();
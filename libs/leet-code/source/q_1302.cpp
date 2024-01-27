#include "q_1302.h"

TreeNode *createNode(int val, TreeNode *left = nullptr, TreeNode *right = nullptr)
{
    return new TreeNode(val, left, right);
}

void deleteTree(TreeNode *node)
{
    if (node)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void leet_test_1302()
{
    Solution_1302 sol;

    TreeNode *r = createNode(1,
                             createNode(2,
                                        createNode(4, createNode(7)),
                                        createNode(5)),
                             createNode(3,
                                        nullptr,
                                        createNode(6, nullptr, createNode(8))));

    int num = sol.deepestLeavesSum(r);
    printf("%d\n", num);

    deleteTree(r);
}

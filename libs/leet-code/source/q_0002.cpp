#include "q_0002.h"

ListNode *createList(const std::vector<int> &values)
{
    if (values.empty())
        return nullptr;

    ListNode *head = new ListNode(values[0]);
    ListNode *current = head;

    for (size_t i = 1; i < values.size(); ++i)
    {
        current->next = new ListNode(values[i]);
        current = current->next;
    }

    return head;
}

void leet_test_0002()
{
    Solution_0002 sol;

    std::vector<int> l1_values = {9, 9, 9, 9, 9, 9, 9};
    std::vector<int> l2_values = {9, 9, 9, 9};

    ListNode *l1 = createList(l1_values);
    ListNode *l2 = createList(l2_values);

    ListNode *answer;
    answer = sol.addTwoNumbers(l1, l2);

    ListNode *current = answer;
    while (current != nullptr)
    {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");

    current = answer;
    while (current != nullptr)
    {
        ListNode *temp = current;
        current = current->next;
        delete temp;
    }
}
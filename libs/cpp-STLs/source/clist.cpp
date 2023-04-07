#include "clist.h"

void list_example()
{
    /* ---------------------------------------------------------------------------------------------------------- */

    /**
     * \brief: [1] std::list
     *    - std::list is a container that supports constant time insertion and removal of elements from anywhere in the container. 
     *    - Fast random access is not supported. 
     *    - It is usually implemented as a doubly-linked list. 
     *    - Compared to std::forward_list this container provides bidirectional iteration capability while being less space efficient.
     *    - Adding, removing and moving the elements within the list or across several lists does not invalidate the iterators or references. 
     *    - An iterator is invalidated only when the corresponding element is deleted.
     * 
     *    - Study std::list<T,Allocator>::merge, std::list<T,Allocator>::splice in cppreferenec.com
     */

    std::list<int> nums1{1, 2, 3, 4 ,5};
    nums1.emplace_back(6);
    nums1.emplace_front(0);

    auto it = std::find(nums1.begin(), nums1.end(), 3);
    if (it != nums1.end())
    {
        nums1.emplace(it, 100);
    }

    for(const auto & num : nums1)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;

    /* ---------------------------------------------------------------------------------------------------------- */
    
    /**
     * \brief: [2] std::forward_list
     *    - std::forward_list is a container that supports fast insertion and removal of elements from anywhere in the container. 
     *    - Fast random access is not supported. 
     *    - It is implemented as a singly-linked list. 
     *    - Compared to std::list this container provides more space efficient storage when bidirectional iteration is not needed.
     *    - Adding, removing and moving the elements within the list, or across several lists, does not invalidate the iterators currently referring to other elements in the list. 
     *    - However, an iterator or reference referring to an element is invalidated when the corresponding element is removed (via erase_after) from the list.
     */

    std::forward_list<int> nums2{1, 2, 3, 4 ,5};
    nums2.emplace_front(0);

    for (auto &num : nums2)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

    /* ---------------------------------------------------------------------------------------------------------- */
}
#include "clamda.h"

int lamda_example()
{
    /**
     * \brief: Lamda expression
     * \details: Constructs a closure: annamed function object capable of captuning variables in scope
     *           [ captures ] <tparams> ( params ) specifiers exception attr -> ret { body }
     *           [ captures ] ( params ) -> ret { body }
     *           [ captures ] ( params ) { body } *** More popular
     *           [ captures ] { body }
     *           [ captures ] → capture by 1)value, 2)reference, and 3)this
     */

    // Lamda expression is same with function object in assembly code
    int three{3};
    int *ptr = &three;
    auto lamdaPlus3 = [localVar = 3, three, &ptr](int x)
    {
        return localVar + three + ptr[0] + x;
    };

    plus plus3{3};
    plus plus5{5};

    std::cout << plus3(10) << std::endl;
    std::cout << plus5(10) << std::endl;
    std::cout << lamdaPlus3(10) << std::endl;
    std::cout << std::endl;

    /* ----------------------------------------------------- */

    /**
     * \brief: Lamda capture [ this ]
     * \details:
     */

    cat1 kitty{1};
    kitty.test();

    std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto lamdaAdd10 = [](int &n)
    {
        n += 10;
    };

    int n = 10;
    lamdaAdd10(n);
    std::cout << n << std::endl;
    
    // example 1)
    std::for_each(nums.begin(), nums.end(), lamdaAdd10);
    // example 2)
    std::for_each(nums.begin(), nums.end(), [](int &n)
    {
        n += 10;
    });

    for (int num : nums)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    /* ----------------------------------------------------- */

    /**
     * \brief: Higher order functions
     * \details:
     */

    

    return 0;
}
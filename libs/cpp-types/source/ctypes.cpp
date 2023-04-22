#include "ctypes.h"

typename std::enable_if<!std::numeric_limits<float>::is_integer, bool>::type
almost_equal(float x, float y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x - y) <= std::numeric_limits<float>::epsilon() * std::fabs(x + y) * ulp
           // unless the result is subnormal
           || std::fabs(x - y) < std::numeric_limits<float>::min();
}

void types_example()
{
    /* ---------------------------------------------------------------------------------------------------------- */

    /**
     * \brief: [1] Floating number
     */

    const float num1 = 0.3f; // ≒ 0.300000011920928955078125
    const float num2 = 0.4f; // ≒ 0.4000000059604644775390625
    const float num3 = 0.7f; // ≒ 0.699999988079071044921875
    const float sum = num1 + num2;

    if (sum == num3)
        std::cout << "sum is 0.7f" << std::endl;
    else
        std::cout << "sum is not 0.7f" << std::endl;

    std::cout << std::setprecision(100) << num1 << std::endl;
    std::cout << std::setprecision(100) << num2 << std::endl;
    std::cout << std::setprecision(100) << num3 << std::endl;
    std::cout << std::setprecision(100) << sum << std::endl;

    std::cout << "------------------------------------- [↑ Example 1-1 ↑] -------------------------------------" << std::endl;

    if (almost_equal(sum, num3, 1))
        std::cout << "sum is 0.7f" << std::endl;
    else
        std::cout << "sum is not 0.7f" << std::endl;

    std::cout << "------------------------------------- [↑ Example 1-2 ↑] -------------------------------------" << std::endl;

    float num = 10000000000;
    for (std::size_t count = 0; count < 10000000; count++)
    {
        num += 1.0;
    }
    // Expected 10010000000, But..
    std::cout << std::setprecision(100) << num << std::endl;

    std::cout << "------------------------------------- [↑ Example 1-3 ↑] -------------------------------------" << std::endl;

    /* ---------------------------------------------------------------------------------------------------------- */
}
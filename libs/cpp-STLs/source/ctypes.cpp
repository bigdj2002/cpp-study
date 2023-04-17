#include "ctypes.h"

void types_example()
{
    const float num1 = 0.0f;
    const float num2 = 0.4f;
    const float sum = num1 + num2;

    if (sum == 0.7f)
        std::cout << "sum is 0.7f" << std::endl;
    else
        std::cout << "sum is not 0.7f" << std::endl;
}
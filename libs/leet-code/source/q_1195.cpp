#include "q_1195.h"

void leet_test_1195()
{
    FizzBuzz_1195 sol(15);
    std::jthread thread1([&sol]()
                         {
        for (int i = 1; i <= sol.getNum(); ++i) {
            if (i % 3 == 0 && i % 5 != 0) {
                sol.fizz([]() { std::cout << "fizz "; });
            }
        } });

    std::jthread thread2([&sol]()
                         {
        for (int i = 1; i <= sol.getNum(); ++i) {
            if (i % 5 == 0 && i % 3 != 0) {
                sol.buzz([]() { std::cout << "buzz "; });
            }
        } });

    std::jthread thread3([&sol]()
                         {
        for (int i = 1; i <= sol.getNum(); ++i) {
            if (i % 15 == 0) {
                sol.fizzbuzz([]() { std::cout << "fizzbuzz "; });
            }
        } });

    std::jthread thread4([&sol]()
                         {
        for (int i = 1; i <= sol.getNum(); ++i) {
            if (i % 3 != 0 && i % 5 != 0) {
                sol.number([i](int num) { std::cout << num << " "; });
            }
        } });

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();

    std::cout << std::endl;
}
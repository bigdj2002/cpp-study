#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

void thread_atomic_example();

struct myStruct1
{
    int a;
    int b;
};

struct myStruct2
{
    int a;
    int b;
    int c[100];
};
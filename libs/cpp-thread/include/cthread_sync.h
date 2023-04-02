#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

void thread_sync_example();

struct mInt
{
  std::mutex m;
  int num = 0;
};
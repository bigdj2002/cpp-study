#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <chrono>
#include <optional>

#define USE_LOCK_TYPE 2    // 0: Normal lock, 1: Lock_guard, 2: unique_lock in plus1()
#define USE_SCLOPED_LOCK 1 // 0: Normal lock, 1: Scoped lock in ab(), ba()

void thread_sync_example();

struct mInt
{
  std::mutex m;
  int num = 0;
};

struct smInt
{
  std::shared_mutex mtx;
  int num = 0;
};

class catSync
{
public:
  catSync()
  {
    std::cout << "cat constructor" << std::endl;
  }

  void speak()
  {
    std::cout << "meow~" << std::endl;
  }
};

class zooSync
{
public:
  zooSync()
  {
    std::call_once(catInitFlag, [this]()
                   { mCat = catSync(); });
  }

private:
  std::optional<catSync> mCat;
  std::once_flag catInitFlag;
};
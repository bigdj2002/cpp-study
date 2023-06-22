#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <chrono>
#include <optional>
#include <condition_variable>
#include <string>
#include <semaphore>
#include <latch>
#include <barrier>
#include <functional>

#define USE_LOCK_TYPE 2    // 0: Normal lock, 1: Lock_guard, 2: unique_lock in plus1()
#define USE_SCOPED_LOCK 1 // 0: Normal lock, 1: Scoped lock in ab(), ba()

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

class singleton
{
public:
  static singleton &getInstance()
  {
    static singleton sObj;
    return sObj;
  }

  // copy constructor, assignment = delete
};

class strStack
{
public:
  // Producer
  void addStr(std::string s)
  {
    {
      std::lock_guard<std::mutex> lck(mMtx);
      mStrs.emplace_back(std::move(s));
    }
    mCv.notify_one();
  }

  // Consumer
  std::string getStr()
  {
    std::unique_lock<std::mutex> lck(mMtx);
    while (mStrs.empty())
    {
      mCv.wait(lck);
    }
    std::string s = std::move(mStrs.back());
    mStrs.pop_back();
    return s;
  }

private:
  std::vector<std::string> mStrs;
  std::mutex mMtx;
  std::condition_variable mCv;
};

class rscManager
{
public:
  void createRsc()
  {
    mSp.acquire();
  }
  void removeRsc()
  {
    mSp.release();
  }

private:
  std::counting_semaphore<2> mSp{2};
};
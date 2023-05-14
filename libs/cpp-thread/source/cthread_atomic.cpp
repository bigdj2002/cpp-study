#include "cthread_atomic.h"

void add_mutex(int &num, std::mutex &lck)
{
    for (int i = 0; i < 10000; i++)
    {
        const std::lock_guard<std::mutex> lock{lck};
        ++num;
    }
}

void add_atomic(std::atomic<int> &num)
{
    for (int i = 0; i < 10000; i++)
    {
        ++num;
    }
}

void thread_atomic_example()
{
    /* ---------------------------------------------------------------------------------------------------------- */

    /**
     * \brief: [1] atomic introduction
     * \details:
     */

    int num1_a = 0;
    std::vector<std::thread> threads1_a, threads1_b;
    std::mutex lock1; // May slow..
    std::atomic<int> num1_b{0};

    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 4; i++)
    {
        threads1_a.emplace_back(add_mutex, std::ref(num1_a), std::ref(lock1));
        ;
    }

    for (auto &thread : threads1_a)
    {
        thread.join();
    }

    std::cout << num1_a << std::endl;
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time1 = end1 - start1;
    std::cout << "Mutex based thread: " << time1.count() * 1000 << std::endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 4; i++)
    {
        threads1_b.emplace_back(add_atomic, std::ref(num1_b));
    }

    for (auto &thread : threads1_b)
    {
        thread.join();
    }

    std::cout << num1_b << std::endl;
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time2 = end2 - start2;
    std::cout << "Atomic based thread: " << time2.count() * 1000 << std::endl;

    std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;

    /* ---------------------------------------------------------------------------------------------------------- */

    /**
     * \brief: [2-1] methods of std::atomic
     * \note: Maybe a lock free system depend on compilers (cfg. std::atomic_flag: 100% lock free)
     * \details:
     *    - Each instantiation and full specialization of the std::atomic template defines an atomic type.
     *    - If one thread writes to an atomic object while another thread reads from it, the behavior is well-defined
     *      (see memory model for details on data races).
     *    - In addition, accesses to atomic objects may establish inter-thread synchronization and order non-atomic memory accesses as specified by std::memory_order.
     *    - std::atomic is neither copyable nor movable.
     *
     * \brief: [2-2] std::atomic_flag
     * \details:
     *    - std::atomic_flag is an atomic boolean type.
     *    - Unlike all specializations of std::atomic, it is guaranteed to be lock-free. (Check using is_lock_free())
     *    - Unlike std::atomic<bool>, std::atomic_flag does not provide load or store operations.
     */

    /** \example: Checking lock free */
    std::atomic<int> num2_a{0};
    std::atomic<float> num2_b{0.0f};
    std::atomic<int *> num2p;
    std::atomic<myStruct1> str2_a;
    // std::atomic<myStruct2> str2_b; // COMPILE ERROR..

    std::cout << std::boolalpha << num2_a.is_lock_free() << std::endl;
    std::cout << std::boolalpha << num2_b.is_lock_free() << std::endl;
    std::cout << std::boolalpha << num2p.is_lock_free() << std::endl;
    std::cout << std::boolalpha << str2_a.is_lock_free() << std::endl;
    // std::cout << std::boolalpha << str2_b.is_lock_free() << std::endl;

    std::cout << "------------------------------------- [↑ Example 2-1 ↑] -------------------------------------" << std::endl;

    /** \example: member functions */
    std::atomic<int> num2_c{0};
    int x2 = 42;
    [[maybe_unused]] int y2 = 0;
    [[maybe_unused]] bool flag2 = 0;

    num2_c.store(x2);                        // MF for storing
    std::cout << "num: " << num2_c.load() << std::endl; // n = x; → COMPILE ERROR! (Deleted)

    x2 = num2_c.load(); // MF for loading
    std::cout << "x: " << x2 << std::endl;

    /** \note: Integer type only */
    num2_c.fetch_add(x2); // MF for adding (Same with 'n += x')
    std::cout << "num: " << num2_c.load() << std::endl;

    y2 = num2_c.exchange(x2); // MF for exchanging (y = num2_c, num2_c = x)
    std::cout << "x: " << x2 << ", y: " << y2 << ", num: " << num2_c.load() << std::endl;

    flag2 = num2_c.compare_exchange_strong(x2, y2);
    /** \details:
     * if (n == x){
     *   n = y;
     *   return true;
     * }
     * else{
     *   x = n;
     *   return false;
     * }
     */
    std::cout << "flag: " << flag2 << ", num: " << num2_c << ", x: " << x2 << ", y: " << y2 << std::endl;

    while (!num2_c.compare_exchange_weak(x2, y2))
    {
        std::cout << "Failed" << std::endl;
    }
    std::cout << "flag: " << flag2 << ", num: " << num2_c << ", x: " << x2 << ", y: " << y2 << std::endl;

    std::cout << "------------------------------------- [↑ Example 2-2 ↑] -------------------------------------" << std::endl;

    /* ---------------------------------------------------------------------------------------------------------- */
}
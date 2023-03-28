#include "cpointer.h"

void foo()
{
  std::cout << "Befor foo" << std::endl;
  std::unique_ptr<cat_pointer> catPtr = std::make_unique<cat_pointer>(3);
  std::vector<cat_pointer> cats(5);
  std::cout << "After foo" << std::endl;
}

void pointer_example()
{
  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [1] Smart pointer basic
   * \details:
   *    1. RAII (Resource Acquisition Is Initialization → Main reason of smart pointer)
   *      - It is a C++ programming technique which binds the life cycle of a resource that must be acquired before use to the lifetime of an object.
   *        (allocated heap memory, thread of execution, open socket, open file, locked mutex, disk space, database connection—anything that exists in limited supply)
   *      - Smart pointer can make to avoid memory leak
   */

  // cat_pointer kitty{1};
  // cat_pointer *catPtr1 = new cat_pointer{3};
  {
    std::unique_ptr<cat_pointer> catPrt2 = std::make_unique<cat_pointer>(3);
    std::cout << "Befor scope" << std::endl;
    {
      std::unique_ptr<cat_pointer> catPrt3 = std::make_unique<cat_pointer>(3);
      foo();
    }
    std::cout << "After scope" << std::endl;
  }

  // delete catPtr1;
  std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [2] Unique pointer
   * \details:
   *    - Exclusive ownership ***
   *    - std::unique_ptr is a smart pointer that owns and manages another object through a pointer and disposes of that object when the unique_ptr goes out of scope.
   *    - The object is disposed of, using the associated deleter when either of the following happens:
   *      # the managing unique_ptr object is destroyed
   *      # the managing unique_ptr object is assigned another pointer via operator= or reset().
   */

  {
    std::unique_ptr<cat_pointer> catPtr3 = std::make_unique<cat_pointer>();
    // std::unique_ptr<cat_pointer> catPtr4 = catPtr3; // Compile ERROR!
    std::unique_ptr<cat_pointer> catPtr4 = std::move(catPtr3);
  }
  std::cout << "------------------------------------- [↑ Example 2 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [3] Shared pointer
   * \details:
   *    - Shared ownership ***
   *    - std::shared_ptr is a smart pointer that retains shared ownership of an object through a pointer.
   *    - Several shared_ptr objects may own the same object. The object is destroyed and its memory deallocated when either of the following happens:
   *      # the last remaining shared_ptr owning the object is destroyed;
   *      # the last remaining shared_ptr owning the object is assigned another pointer via operator= or reset().
   *    - The object is destroyed using delete-expression or a custom deleter that is supplied to shared_ptr during construction.
   *    - A shared_ptr can share ownership of an object while storing a pointer to another object.
   *    - A shared_ptr may also own no objects
   */

  {
    {
      cat_pointer *catPtr5 = new cat_pointer();
      [[maybe_unused]] cat_pointer *catPtr6 = catPtr5;

      std::shared_ptr<cat_pointer> catPtr7 = std::make_shared<cat_pointer>();
      std::cout << "Ref count: " << catPtr7.use_count() << std::endl;
      std::shared_ptr<cat_pointer> catPtr8 = catPtr7;
      std::cout << "Ref count: " << catPtr7.use_count() << std::endl;

      delete catPtr5;
    }

    {
      std::shared_ptr<cat_pointer> mPtr = std::make_shared<cat_pointer>();
      std::cout << "Ref count: " << mPtr.use_count() << std::endl;
      // mPtr->mVar = mPtr; // *** Memory leak! (But not compile error)
      // std::cout << "Ref count: " << mPtr.use_count() << std::endl;
    }

    {
      std::shared_ptr<cat_pointer> pKitty = std::make_shared<cat_pointer>();
      std::shared_ptr<cat_pointer> pNabi = std::make_shared<cat_pointer>();
      // pKitty->mFriend = pNabi;
      // std::cout << "Ref count: " << pKitty.use_count() << std::endl;
      // pNabi->mFriend = pKitty;
      // std::cout << "Ref count: " << pNabi.use_count() << std::endl;
      // Life cycle is eternal (Ref count = 1) -> Cannot resolve to free memory
    }
  }

  std::cout << "------------------------------------- [↑ Example 3 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */

  /**
   * \brief: [4] Weak pointer
   * \details:
   *    - std::weak_ptr is a smart pointer that holds a non-owning ("weak") reference to an object that is managed by std::shared_ptr.
   *    - It must be converted to std::shared_ptr in order to access the referenced object.
   *    - std::weak_ptr models temporary ownership: when an object needs to be accessed only if it exists, and it may be deleted at any time by someone else,
   *      std::weak_ptr is used to track the object, and it is converted to std::shared_ptr to assume temporary ownership.
   *    - If the original std::shared_ptr is destroyed at this time, the object's lifetime is extended until the temporary std::shared_ptr is destroyed as well.
   */

  {
    std::weak_ptr<cat_pointer> wPtr;
    {
      std::shared_ptr<cat_pointer> sPtr = std::make_shared<cat_pointer>();
      wPtr = sPtr;
      std::cout << "Ref count: " << sPtr.use_count() << std::endl;

      if (const auto spt = wPtr.lock())
      {
        std::cout << "Ref count: " << spt.use_count() << std::endl;
        spt->speak();
      }
      else
      {
        std::cout << "Pointing nothing" << std::endl;
      }
    }
  }

  std::cout << "------------------------------------- [↑ Example 4 ↑] -------------------------------------" << std::endl;

  /* ---------------------------------------------------------------------------------------------------------- */
}
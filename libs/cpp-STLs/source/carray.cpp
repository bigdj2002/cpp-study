#include "carray.h"

void fnarray()
{
  std::array<int, 100> nums;
  nums.fill(0);
  for (const int n : nums)
  {
    std::cout << n << " ";
  }
  std::cout << std::endl;
}

void fnvector()
{
  std::vector<int> nums(100);
  nums.reserve(1000);
}

void array_example()
{
  /**
   * \brief: [1] Array VS Vector
   * common: sequential memory (Supports random access)
   * Array:  Stack / Compile time / fixed size     / limited to stack size
   * Vector: Heap  / Runtime      / variable size  / huge memory size
   */

  fnarray();
  fnvector();
  std::cout << "------------------------------------- [↑ Example 1 ↑] -------------------------------------" << std::endl;




  /**
   * \brief: [2] std::array - mutliple dimension
   */

  using N2Mat3x3 = std::array<std::array<int, 3>, 3>; // alias template
  N2Mat3x3 fixedMat;
  std::vector<std::vector<int>> dynamicMat(3, std::vector<int>(3));

  fixedMat[1][1] = 5;
  fixedMat[2][2] = 1; // array: Sequantial memory allocation
  dynamicMat[1][1] = 5;
  dynamicMat[0][2] = 10; // vector: dynamic memory allocation

  /** \example: #1 */
  MatrixEx1<int> mat1(10, 10);
  MatrixEx2<int, 10, 10> mat2; // Exactly same with mat1! Just difference of row/col are generated when compiled;
  mat1(3, 3) = 3;
  mat1(4, 3) = mat1(3, 3) * 10;
  std::cout << mat1(4, 3) << std::endl;
  std::cout << "------------------------------------- [↑ Example 2-1 ↑] -------------------------------------" << std::endl;

  /** \example: #1 */
  constexpr int matSize = 1000;
  std::array<std::array<int, matSize>, matSize> mat3;
  // method 1: faster than method 2 (x100 ~ x1000) due to the cache line issue for copying
  const auto t1 = std::chrono::high_resolution_clock::now();
  for (int rowIdx = 0; rowIdx < matSize; rowIdx++)
  {
    for (int colIdx = 0; colIdx < matSize; colIdx++)
    {
      mat3[rowIdx][colIdx] = 1;
    }
  }
  const auto t2 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time1 = (t2 - t1);
  std::cout << "Loop method 1: " << time1.count() << std::endl;

  // method 2
  const auto t3 = std::chrono::high_resolution_clock::now();
  for (int colIdx = 0; colIdx < matSize; colIdx++)
  {
    for (int rowIdx = 0; rowIdx < matSize; rowIdx++)
    {
      mat3[rowIdx][colIdx] = 1;
    }
  }
  const auto t4 = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> time2 = (t4 - t3);
  std::cout << "Loop method 2: " << time2.count() << std::endl;
  std::cout << "------------------------------------- [↑ Example 2-2 ↑] -------------------------------------" << std::endl;




  /**
   * \brief: [3] std::deque - mutliple dimension
   * \details: 'deque' stands for 'Double Ended Queue'
   * \details: deque: O(1) time complexity for random access
   * \details: Cons 1(VS Vector): Need to double pointer dereferencing to access
   * \details: Cons 2(VS Vector): Casuing cache miss due to the chunked memory allocation
   */
  /** \example: #1 in cppreference.com */
  // Create a deque containing integers
  std::deque<int> d = {7, 5, 16, 8};

  // Add an integer to the beginning and end of the deque
  d.push_front(13);
  d.push_back(25);
  d.emplace_front(26); // More efficient than push_front
  d.emplace_back(123); // More efficient than push_back

  // Iterate and print values of deque
  for (int n : d)
    std::cout << n << ' ';
  std::cout << std::endl;
  std::cout << "------------------------------------- [↑ Example 3 ↑] -------------------------------------" << std::endl;
}
#include <array>
#include <vector>
#include <iostream>
#include <chrono>
#include <deque>
#include <functional>

void array_example();

template <typename T>
class MatrixEx1
{
public:
  MatrixEx1(int row, int col) : mMatrix(row * col, 0)
  {
    m_row = row;
    m_col = col;
  }
  T &operator()(int rowIdx, int colIdx)
  {
    const int idx = rowIdx * m_col + colIdx;
    return mMatrix[idx];
  }

private:
  std::vector<T> mMatrix;
  int m_row;
  int m_col;
};

template <typename T, int ROW, int COL>
class MatrixEx2
{
public:
  MatrixEx2() : mMatrix(ROW * COL, 0) {}
  T &operator()(int rowIdx, int colIdx)
  {
    const int idx = rowIdx * COL + colIdx;
    return mMatrix[idx];
  }

private:
  std::vector<T> mMatrix;
};
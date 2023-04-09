#include <stack>
#include <iostream>
#include <vector>

void stack_example();

class RingBufferStack
{
public:
  RingBufferStack(int size) : buffer(size), top(0) {}

  void push(int value)
  {
    if (top == buffer.size())
    {
      std::cerr << "Ring buffer stack is full!" << std::endl;
      return;
    }
    buffer[top++] = value;
  }

  int pop()
  {
    if (top == 0)
    {
      std::cerr << "Ring buffer stack is empty!" << std::endl;
      return -1;
    }
    int value = buffer[--top];
    return value;
  }

  bool empty() const
  {
    return top == 0;
  }

  int size() const
  {
    return top;
  }

private:
  std::vector<int> buffer;
  size_t top;
};
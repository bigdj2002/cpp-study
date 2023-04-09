#include <queue>
#include <iostream>

void queue_example();

class RingBufferQueue
{
public:
  RingBufferQueue(int size) : buffer(size), head(0), tail(0), count(0) {}

  void push(int value)
  {
    if (count == buffer.size())
    {
      buffer[head] = value;
      head = (head + 1) % buffer.size();
    }
    else
    {
      buffer[tail] = value;
      tail = (tail + 1) % buffer.size();
      ++count;
    }
  }

  int pop()
  {
    if (count == 0)
    {
      std::cerr << "Ring buffer queue is empty!" << std::endl;
      return -1;
    }
    int value = buffer[head];
    head = (head + 1) % buffer.size();
    --count;
    return value;
  }

  bool empty() const
  {
    return count == 0;
  }

  int size() const
  {
    return count;
  }

private:
  std::vector<int> buffer;
  size_t head;
  size_t tail;
  size_t count;
};
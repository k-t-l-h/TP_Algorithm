/*
3_2. Реализовать дек с динамическим зацикленным буфером.
*/

#include <iostream>
#include <cstring>

#define START_SIZE 16
using namespace std;

class Deque
{
public:
  //правило пяти
  ~Deque();
  Deque(const Deque&) = delete;
  Deque(const Deque&&) = delete;
  Deque& operator = (const Deque&) = delete;
  Deque& operator = (Deque&&) = delete;

  Deque(int size): buffer_size(size), head(0), tail(0), size(0)
  {
    buffer = new int[buffer_size];
  };

  Deque(): buffer_size(START_SIZE), head(0), tail(0), size(0)
  {
    buffer = new int[buffer_size];
  };

  void push_back(int value);
  int pop_back();
  void push_front(int value);
  int pop_front();

private:

  int head;
  int tail;
  int* buffer;

  //максимальный размер
  int buffer_size;
  //реальный размер
  int size;

  void resize();
};

Deque::~Deque()
{
  delete[] buffer;
}

void Deque::push_back(int value)
{
  if (!size)
  {
    tail = -1;
  }

  if (size == buffer_size)
  {
    resize();
  }

  tail = (tail + 1) % buffer_size;
  buffer[tail] = value;
  size++;
}

void Deque::push_front(int value)
{
  if (!size)
  {
    head = 1;
  }

  if (size == buffer_size)
  {
    resize();
  }

  head  = (head  + buffer_size - 1 ) % buffer_size;
  buffer[head] = value;
  size++;
}

int Deque::pop_back()
{
  if (!size)
  {
    return -1;
  }

  int result = buffer[tail];
  //для зацикливания
  tail = (tail + buffer_size - 1) % buffer_size;
  size--;

  if (!size)
  {
    head = 0;
    tail = 0;
  }

  return result;

}

int Deque::pop_front()
{
  if (!size)
  {
    return -1;
  }

  int result = buffer[head];
  head = (head + 1) % buffer_size;
  size--;

  if (!size)
  {
    head = 0;
    tail = 0;
  }

  return result;
}


void Deque::resize()
{
  int size = buffer_size;
  buffer_size = buffer_size << 1;

  int* buf = new int[buffer_size];

  for ( int i = 0; i < size; i++)
  {
    buf[i] = buffer[(i + head) % size];
  }
  delete[] buffer;
  buffer = buf;
  head = 0;
  tail = size-1;
}

int main() {

  Deque deque;
  long n = 0;
  cin >> n;

  for (size_t i = 0; i < n; i++) {
    int operation = 0;
    int value = -1;
    int check = -1;

     std::cin >> operation >> value;

     switch (operation) {
       case 1:
        deque.push_front(value);
       break;

       case 2:
       check = -1;
       check = deque.pop_front();

       if (check != value)
       {
         cout << "NO" << '\n';
         return 0;
       }
       break;

       case 3:
        deque.push_back(value);
       break;

       case 4:
       check = -1;
       check = deque.pop_back();

       if (check != value)
       {
         cout << "NO" << '\n';
         return 0;
       }
       break;

       default:
         cout << "NO" << '\n';
         return 0;
     }
  }

  cout << "YES" << '\n';

  return 0;
}

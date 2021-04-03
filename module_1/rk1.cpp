//Дана последовательность, состоящая из символов '(' и ')'. Требуется определить,
//является ли данная последовательность правильной скобочной последовательностью. 
//Длина исходной последовательности ≤ 800000.

#include <iostream>

#define START_SIZE 16
using namespace std;

class Stack {
public:
    //правило пяти
    ~Stack();
    Stack(const Stack &) = delete;
    Stack(const Stack &&) = delete;
    Stack & operator = (const Stack &) = delete;
    Stack & operator = (Stack &&) = delete;

    Stack(): buffer_size(0), size(0), buffer(nullptr) {};

    void push(int value);
    int pop();
    int get_size();

private:
    int* buffer;
    //максимальный размер
    int buffer_size;
    //реальный размер
    int size;

    void resize();
};

Stack::~Stack()
{
    delete[] buffer;
}

void Stack::push(int value)
{
    if (buffer == nullptr) {
        buffer = new int[START_SIZE];
        size = 0;
        buffer_size = START_SIZE;
    }

    if (size == buffer_size)
    {
        resize();
    }
    buffer[size] = value;
    size++;
}

int Stack::pop()
{
    if (buffer == nullptr) {
        buffer = new int[START_SIZE];
        size = 0;
        buffer_size = START_SIZE;
    }

    if (!size)
    {
        return -1;
    }

    int result = buffer[size];
    size--;
    return result;
}


void Stack::resize()
{
    int size = buffer_size;
    buffer_size = buffer_size << 1;

    int* buf = new int[buffer_size];

    for ( int i = 0; i < size; i++)
    {
        buf[i] = buffer[i];
    }
    delete[] buffer;
    buffer = buf;
}

int Stack::get_size() {
        return size;
};

int main() {
    Stack dq;
    char c;

    while( (c=getchar()) != '\n' )
    {
        switch (c) {
            case '(':
                dq.push(1);
                break;

            case ')':
                int a = dq.pop();
                if (a == -1) {
                    cout << "NO";
                    return 0;
                }
                break;
        }
    }

    if (dq.get_size() != 0 ) {
        cout << "NO";
    } else {
        cout << "YES";
    }
    return 0;
}

//
// Created by ktlh on 10.03.2021.
//

/*
 * 3_1. Реализовать очередь с динамическим зацикленным буфером.
 */

#include <iostream>

#define DEFAULT_SIZE 16

using namespace std;

class Queue {
public:
    ~Queue();
    Queue(const Queue&) = delete;
    Queue(const Queue&&) = delete;
    Queue& operator=(const Queue&) = delete;
    Queue& operator=(Queue&&) = delete;

    Queue() : buffer_size(0), head(0), tail(0), size(0), buffer(nullptr) {}
    void push_back(int value);
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

//увеличиваем наш буффер
void Queue::resize() {
    if (buffer == nullptr) {
      buffer = new int[DEFAULT_SIZE];
      buffer_size = DEFAULT_SIZE;
      return;
    }
    //увеличиваем сразу в два раза
    int new_size = buffer_size << 1;

    int* new_buffer = new int[new_size];

    for (int i = 0; i < buffer_size; i++) {
        new_buffer[i] = buffer[(i + head) % buffer_size];
    }

    delete[] buffer;

    buffer = new_buffer;
    head = 0;
    tail = size;
    buffer_size = new_size;
}

Queue::~Queue() { delete[] buffer; }

void Queue::push_back(int value) {

    //если достигнут потолок
    if (size == buffer_size) {
        resize();
    }

    buffer[tail] = value;
    tail = (tail + 1) % buffer_size;
    size++;
};

int Queue::pop_front() {
    //если нет элементов
    if (!size) {
        return -1;
    }

    int value = buffer[head];
    head = (head + 1) % buffer_size;
    size--;

    //облегчаем жизнь на будущее
    if (!size) {
        head = 0;
        tail = 0;
    }

    return value;
};

int main() {
    Queue queue;

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int operation;
        int reference;
        int value;

        cin >> operation >> reference;
        switch (operation) {
            // pop
            case 2:
                value = queue.pop_front();
                if (value != reference) {
                    cout << "NO" << '\n';
                    return 0;
                }
                break;
            // push
            case 3:
                queue.push_back(reference);
                break;
        }
    }

    cout << "YES" << '\n';
    return 0;
}
//
// Created by ktlh on 10.03.2021.
//

/*
 * 4_2. Быстрое сложение.
 * Для сложения чисел используется старый компьютер.
 * Время, затрачиваемое на нахождение суммы двух чисел равно их сумме.
 * Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время,
 * в зависимости от порядка вычислений.
 * Требуется написать программу, которая определяет минимальное время,
 * достаточное для вычисления суммы заданного набора чисел.
 */
#include <iostream>
#define DEFAULT_SIZE 16

using namespace std;

struct Less
{
    bool operator ()(const int& l, const int& r)  {return l < r;}
};


template<class Comparator>
class BinaryHeap{
public:

    BinaryHeap(Comparator comparator = Comparator()):
            max_size(DEFAULT_SIZE), real_size(0)
    {
        heap_array = new int[DEFAULT_SIZE];
        cmp = comparator;
    };
    ~BinaryHeap(){
        delete[] heap_array;
    };
    BinaryHeap(const BinaryHeap&) = delete;
    BinaryHeap(const BinaryHeap&&) = delete;
    BinaryHeap& operator=(const BinaryHeap&) = delete;
    BinaryHeap& operator=(BinaryHeap&&) = delete;

    void Insert(int value) {
        if (real_size  == max_size) {
            Resize();
        }

        heap_array[real_size] = value;
        ShiftUp(real_size);
        real_size++;
    };

    int Extract() {
        if (real_size == 0) {
            return -1;
        }

        int value = heap_array[0];
        real_size--;
        if (real_size != 0) {
            swap(heap_array[0], heap_array[real_size]);
            ShiftDown(0);
        }
        return value;
    };

    void ShiftUp(int index) {

        while(index > 0)
        {
            int parent = (index - 1) / 2;

            if (heap_array[index] <= heap_array[parent] ) {
                swap(heap_array[index], heap_array[parent]);
            }
            index = parent;
        }
    };

    unsigned int real_size;

    void PrintHeap(){

        for( int i = 0; i < real_size; ++i ) {
            std::cout << heap_array[i] << " ";
        }
        std::cout << std::endl;
    };

private:
    int* heap_array;
    unsigned int max_size;
    Comparator cmp;

    void BuildHeap(){

        for (int i = real_size / 2 - 1; i >= 0; --i)
        {
            ShiftDown(i);
        }
    };

    void ShiftDown(int index){
        int left = 2*index + 1;
        int right = 2*index + 2;

        int largest = index;

        if (left < real_size && cmp(heap_array[left], heap_array[largest])) {
            largest = left;
        }

        if (right < real_size && cmp(heap_array[right], heap_array[largest])) {
            largest = right;
        }

        if (largest != index) {
            swap(heap_array[index], heap_array[largest]);
            ShiftDown(largest);
        }
    };

    void Resize() {
        int* new_heap_array = new int[max_size<<1];
        copy(heap_array, heap_array + real_size, new_heap_array);
        delete[] heap_array;
        heap_array = new_heap_array;
        max_size = max_size << 1;
    };

};

int main() {
    //собираем кучу
    short int n = 0; //n < 100
    int value = 0; //<= 1 000 000 000

    int sum = 0;

    BinaryHeap<Less> heap;

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> value;
        heap.Insert(value);
    }

    //до тех пор, пока куча не пуста
    //здесь как минимум 2 объекта
    while (heap.real_size > 1) {
        int a = heap.Extract();
        int b = heap.Extract();

        sum += a + b;
        heap.Insert(a+b);
    }

    cout << sum;

    return 0;

}
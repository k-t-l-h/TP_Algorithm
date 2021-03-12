//
// Created by ktlh on 10.03.2021.
//

/*
 * 6_2. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от конца
 * массива к началу.
 */

#include <iostream>

using namespace std;

struct GE {
    bool operator()(const int& l, const int& r) { return l >= r; }
};

unsigned int median_of_three(int* arr, unsigned int start, unsigned int end) {
    int middle = start + (end - start) / 2;

    if ((arr[start] > arr[middle]) ^ (arr[start] > arr[end])) {
        return start;
    } else if ((arr[middle] < arr[start]) ^ (arr[middle] < arr[end])) {
        return middle;
    } else {
        return end;
    }
}

template <class Comparator>
int partition(int* arr, unsigned int start, unsigned int end, Comparator cmp) {
    unsigned int pivot = median_of_three(arr, start, end);

    int value = arr[pivot];

    if (pivot != start) {
        swap(arr[pivot], arr[start]);
        pivot = start;
    }

    //проход двух итераторов от конца к началу
    int i = end - 1;
    int j = end - 1;

    for (j; j > start; j--) {
        if (cmp(arr[j], value)) {
            if (j != i) {
                swap(arr[i], arr[j]);
            }
            i--;
        }
    }

    if (pivot != i) {
        swap(arr[i], arr[pivot]);
    }

    return i;
}

template <class Comparator>
void K_stat(int* array, unsigned int size, unsigned int k, Comparator cmp) {
    unsigned int start = 0;
    unsigned int end = size;

    unsigned  int pivot = partition(array, start, end, cmp);

    while (pivot != k) {
        if (pivot > k) {
            end = pivot;
        } else {
            start = pivot + 1;
        }
        pivot = partition(array, start, end, cmp);
    }
}

int main(int argc, const char* argv[]) {
    unsigned int n, k;
    cin >> n >> k;

    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    K_stat(arr, n, k, GE());

    cout << arr[k];

    return 0;
}

//
// Created by ktlh on 10.03.2021.
//

/*
 *  Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел
 * B[0..m-1].
 *  Для каждого элемента массива B[i] найдите минимальный индекс k минимального
 * элемента массива A,
 *  равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет,
 * выведите n. n, m ≤ 10000.
 */

#include <iostream>
using namespace std;

int binary_search(long reference, long *arr, unsigned int size) {
    if (arr[0] >= reference) {
        return 0;
    }
    if (reference > arr[size - 1]) {
        return size;
    }

    //начало, размер интервала, конец
    unsigned int start = 0;
    unsigned int k = 1;
    unsigned int end = start + k;

    long last = arr[end];
    while (last < reference) {
        start = end;
        k = k << 1;
        end = start + k;

        if (end >= size) {
            end = size - 1;
            break;
        }

        last = arr[end];
    }

    unsigned int middle = 0;
    while (start < end) {
        middle = start + (end - start) / 2;

        if (reference <= arr[middle]) {
            end = middle;
        } else {
            start = middle + 1;
        }
    }

    if (end == size - 1 && arr[end - 1] == reference) {
        end -= 1;
    }

    return end;
}

int main() {
    unsigned int a_size = 0;
    unsigned int b_size = 0;

    cin >> a_size >> b_size;
    long *A = new long[a_size];

    for (unsigned int i = 0; i < a_size; i++) {
        cin >> A[i];
    }

    long *B = new long[b_size];

    for (unsigned int i = 0; i < b_size; i++) {
        cin >> B[i];
    }

    for (unsigned int i = 0; i < b_size; i++) {
        cout << binary_search(B[i], A, a_size) << " ";
    }

    delete[] A;
    delete[] B;

    return 0;
}

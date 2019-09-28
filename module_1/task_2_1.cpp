/*
2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел
B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс k
минимального элемента массива A, равного или превосходящего B[i]:
A[k] >= B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000.
*/

#include <iostream>
using namespace std;

int get_nearest(long key, long *arr, long arr_size) {
  long index = 0;

  //в массиве 1 элемент или первый элемент больше или равен ключу
  if (arr_size == 1 || arr[0] >= key) {
    index = 0;
    return index;
  } else {
    long start = 0;
    long distance = 1;
    long finish = start + distance;

    //поиск нужного промежутка
    while (arr[finish] < key) {
      start = finish;
      distance *= 2;
      finish = start + distance;

      if (finish >= arr_size) {
        finish = arr_size - 1;
        break;
      }
    }

    //ключ больше любого элемента в массиве
    //вернуть n
    if (key > arr[finish]) {
      return arr_size;
    }

    long mid = 0;
    //бинарный поиск
    while (start < finish)  //пока значения не совпали
    {
      mid = start + (finish - start) / 2;  //защита от переполнения

      if (key <= arr[mid])  //ключ в правой половине
      {
        finish = mid;
      } else  //ключ в левой половине
      {
        start = mid+1;
      }
    }
  }
  index = finish;


  return index;
}

int main() {
  //ввод массивов
  long a_size, b_size = 0;

  cin >> a_size >> b_size;
  long *a_arr = new long[a_size];

  for (long i = 0; i < a_size; i++) {
    cin >> a_arr[i];
  }

  long *b_arr = new long[b_size];

  for (long i = 0; i < b_size; i++) {
    cin >> b_arr[i];
  }

  for (long i = 0; i < b_size; i++) {
    cout << get_nearest(b_arr[i], a_arr, a_size) << " ";
  }

  //освобождение памяти
  delete[] a_arr;
  delete[] b_arr;

  return 0;
}

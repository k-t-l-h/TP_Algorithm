/*
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9]
размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число,
которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
*/

#include <iostream>
#include <random>
#include <ctime>

using namespace std;

struct GE {
  bool operator()(const int& l, const int& r) { return l > r; }
};

int random_pivot( int l, int r)
{
  srand(time(NULL));
  return ( l + rand() % (r - l));
}


template <class Comparator>
int partition(int* arr, int start, int end, Comparator cmp) {
  int pivot = random_pivot(start, end);

  int value = arr[pivot];

  if (pivot != start){
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
void K_stat(int* array, int size, int k, Comparator cmp) {
  int start = 0;
  int end = size;

  int pivot = partition(array, start, end, cmp);

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
  int n, k;
  cin >> n >> k;

  int* arr = new int[n];
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  K_stat(arr, n, k, GE());
  cout << arr[k];

  delete[] arr;

  return 0;
}

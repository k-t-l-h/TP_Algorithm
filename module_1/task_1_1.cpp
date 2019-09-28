/*
1_1. Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
 Необходимо найти первую пару индексов i0 и j0, i0 ≤ j0, такую что
 A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.

Требования: Время работы - O(n).
n ≤ 100000.
*/

#include <iostream>
using namespace std;

void find_max_sum(long *a_arr, long *b_arr, long size, long* a_ind, long* b_ind)
{
    long sum = a_arr[0] + b_arr[0];

    long tmp_ind = 0;

    for (long i = 0; i < size; i++)
    {
        if (a_arr[tmp_ind] < a_arr[i])
        {
          tmp_ind = i;
        }

        if ( a_arr[tmp_ind] + b_arr[i] > sum)
        {
          *b_ind = i;
          *a_ind = tmp_ind;
          sum = a_arr[*a_ind] + b_arr[*b_ind];
        }


    }
}


int main()
{

    //массивы одинаковой длины
    long size = 0;

    cin >> size;
    long *a_arr = new long[size];

    for (long i = 0; i < size; i++)
    {
        cin >> a_arr[i];
    }
    long *b_arr = new long[size];

    for (long i = 0; i < size; i++)
    {
        cin >> b_arr[i];
    }

    //индексы максимальных элементов
    long a_ind = 0;
    long b_ind = 0;

    //обход массивов
    find_max_sum(a_arr, b_arr, size, &a_ind, &b_ind);

    //вывод результатов
    cout << a_ind << " " << b_ind;

    //освобождение памяти
    delete[] a_arr;
    delete[] b_arr;

    return 0;
}

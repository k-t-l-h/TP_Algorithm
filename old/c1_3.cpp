/*
1_3. Даны два строго возрастающих массива целых чисел A[0..n)
и B[0..m) и число k. Найти количество таких пар индексов (i, j),
что A[i] + B[j] = k. Время работы O(n + m). n, m ≤ 100000.
*/

//стиль кода: GNU

#include <iostream>
using namespace std;

long equal_check(long *a_arr, long a_arr_size, 
				 long *b_arr, long b_arr_size, long equal_to)
{
    long result = 0;

    long a_p = 0; //первый массив обходим с начала
    long b_p = b_arr_size - 1; //второй массив обходим с конца

    for (a_p = 0; a_p < a_arr_size; ++a_p)
    {
        while ((a_arr[a_p] + b_arr[b_p] >= equal_to) && (b_p >= 0))
        {
            if (a_arr[a_p] + b_arr[b_p] == equal_to)
            {
                result++;
            }
            --b_p;
        }
    }

    return result;
}

int main()
{

    //ввод массивов
    long a_size, b_size = 0;

    cin >> a_size;
    long *a_arr = new long[a_size];

    for (long i = 0; i < a_size; i++)
    {
        cin >> a_arr[i];
    }

    cin >> b_size;
    long *b_arr = new long[b_size];

    for (long i = 0; i < b_size; i++)
    {
        cin >> b_arr[i];
    }

    //некоторая константа
    long k = 0;
    cin >> k;

    long result = 0;
    //обход массивов

    result = equal_check(a_arr, a_size, b_arr, b_size, k);

    //вывод результатов
    cout << result;

    //освобождение памяти
    delete[] a_arr;
    delete[] b_arr;

    return 0;
}

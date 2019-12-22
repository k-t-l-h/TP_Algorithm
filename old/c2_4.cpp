/*
2_4. Дан отсортированный массив различных целых чисел A[0..n-1] 
и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i]
найдите минимальный индекс элемента массива A[k], 
ближайшего по значению к B[i]. n ≤ 110000, m ≤ 1000. 
Время работы поиска для каждого элемента B[i]: O(log(k)).
*/

//стиль кода: GNU
#include <iostream>
#include <cmath>
using namespace std;

int get_nearest(long key, long *arr, long arr_size)
{
	long index = -1;
	
	//некорректные данные
	if (arr_size < 1)
	{
		return index;
	}
	
	//в массиве 1 элемент или первый элемент ближайший	
	if (arr_size == 1 || key < arr[0]) 
	{
		index = 0;
		return index;
	}
	else
	{
		long start = 0;
		long distance = 1;
		long finish = start + distance;
		
		//поиск нужного промежутка
		while (arr[finish] < key)
		{
			start = finish;
			distance *= 2;
			finish = start + distance;
			
			if (finish >= arr_size)
			{
				finish = arr_size - 1;
				break; //дошли до последнего интервала
			}
		}
		
		//ключ больше любого элемента в массиве
		if (key > arr[finish])
		{
			return finish;
		}
		
		long mid = 0;
		//бинарный поиск 
		while (finish - start > 1) //пока значения не совпали
		{
			mid = start + (finish - start) / 2; //защита от переполнения
			if (key > arr[mid]) //ключ в правой половине
			{
				start = mid;
			}
			else //ключ в левой половине
			{
				finish = mid;
			}			
		}
		
		//выбор наименьшего элемента
		if ( abs(arr[finish] - key) > abs(arr[start] - key))
		{
			return finish;
		}
		else
		{
			return start;
		}
	}
	
	return index;
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
	
	for (long i = 0; i < b_size; i++)
	{
		cout << get_nearest(b_arr[i], a_arr, a_size) << " ";
	}
	
	//освобождение памяти
    delete[] a_arr;
    delete[] b_arr;

	
	return 0;
}

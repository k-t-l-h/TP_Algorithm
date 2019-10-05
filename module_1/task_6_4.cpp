/*
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9]
размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число,
которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
*/

#include <iostream>
#include <random>
#include <ctime>


int random_pivot( int l, int r)
{
		srand(time(NULL));
		return ( l + rand() % (r - l));
}
template<class Compare>
int partition(int* arr, int l, int r, Compare cmp)
{
	int pivot = random_pivot(l, r);
	//std::cout << "Check "<< l << " " << r << " " << pivot << '\n';
	int value = arr[pivot];
	if (pivot != l){
		std::swap(arr[pivot], arr[l]);
		pivot = l;
	}
	//отсчёт с конца
	int i = r - 1;
	int j = r - 1;

	for(j; j > l; j--)
	{
		if(cmp(arr[j], value))
		{
			if (j != i)
						std::swap(arr[i], arr[j]);
			i--;
		}
	}

	if (pivot != i)
	{
		std::swap(arr[i], arr[pivot]);
	}

	return i;
}

template<class Compare>
void K_stat(int* array, size_t size, int k, Compare cmp)
{
	int l = 0;
	int r = size;

	int rp = 0;

	while(l < r)
	{
		/*for(size_t i = 0; i < size; i++){
			 std::cout << array[i] << " "; }
			 std::cout << "" << '\n';*/

		rp = partition(array, l, r, cmp);

		if (rp == k)
		{
			return;
		}

		if (rp > k)
		{
			r = rp;
		}
		else
		{
			l = rp + 1;
		}
	}

}

int main(int argc, const char * argv[]) {

	int n, k;
	std::cin >> n >> k;


	int* array = new int[n];
	for (int i = 0; i < n; i++)
	{
		std::cin >> array[i];
	}

	K_stat(array, n, k, [](const int& l, const int& r) const {return l >= r;});

	std::cout << array[k];

	return 0;

}

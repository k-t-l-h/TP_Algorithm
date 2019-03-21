#include <iostream>

int medianOfThree(int* array, int l, int r)
{
	int m = l + (r - l)/2; 
	
	return m;
}

int partition(int* arr, int l, int r) 
{
	int pivot = medianOfThree(arr, l, r); 
	
	int value = arr[pivot];
	
	std::swap(arr[pivot], arr[r-1]);
	
	int i = l;
	int j = r - 1;
	
	while(i < j) 
	{
		for(; arr[i] < value; i++)
		{
			
		}
		
		while( j >= 0 && arr[--j] >= value);
		
		if (i < j) 
		{
			std::swap(arr[i], arr[j]);
		}
	}
	
	std::swap(arr[i], arr[r-1]);
	
	return i;
}

void K_stat(int* array, size_t size, int k)
{
	int l = 0;
	int r = size;
	
	int m = 0;
	
	while(l < r)
	{
		m = partition(array, l, r);
		
		if (m == k)
		{
			return;
		}
		
		if (m > k)
		{
			r = m;
		}
		else
		{
			l = m + 1;
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
	
	K_stat(array, n, k);
	
	std::cout << array[k];
	
	return 0;
	
}
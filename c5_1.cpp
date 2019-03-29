#include <iostream>
#include <cstring>


struct Pair {
    int come;
    int leave;
    Pair() : come(0), leave(0) {}
    Pair(int x, int y) : come(x), leave(y) {}
    
};


void merge(Pair* Left, size_t left_s, Pair* Right, size_t right_s, Pair* Result) 
{ 
	size_t l_i, r_i, res_i;
	l_i = 0;
	r_i = 0;
	res_i = 0;
	
	while (l_i < left_s && r_i < right_s) 
    { 
		if (Left[l_i].leave <= Right[r_i].leave)
		{
			if (Left[l_i].leave == Right[r_i].leave)
			{
				if (Left[l_i].come > Right[r_i].come)
				{
					Result[res_i].come = Left[l_i].come;
					Result[res_i].leave = Left[l_i].leave;
					l_i++;
				}
				else
				{
					Result[res_i].come = Right[r_i].come;
					Result[res_i].leave = Right[r_i].leave;
					r_i++;
				}
			}
			else
			{
				Result[res_i].come = Left[l_i].come;
				Result[res_i].leave = Left[l_i].leave;
				l_i++;
			}
		}
		else
		{
			Result[res_i].come = Right[r_i].come;
			Result[res_i].leave = Right[r_i].leave;
			r_i++;
		}
		
		res_i++;
    } 
	
	if (l_i == left_s)
	{
		while( r_i != right_s)
		{
			Result[res_i].come = Right[r_i].come;
			Result[res_i].leave = Right[r_i].leave;
			r_i++; 
			res_i++;
		}
	}
	else
	{
		while( l_i != left_s)
		{
			Result[res_i].come = Left[l_i].come;
			Result[res_i].leave = Left[l_i].leave;
			l_i++;
			res_i++;
		}
	}
} 
  
  
void merge_sort(Pair* array, size_t size)
{
	if (size <= 1)
		return;
	
	size_t first = size / 2;
	size_t second = size - first;
	
	merge_sort( array, first );
	merge_sort( array + first, second );
	
	Pair*  tmp = new Pair[size];
	merge(array, first, array + first, second, tmp);
	
	memcpy(array, tmp, sizeof( Pair ) * size );
	delete[] tmp;
}

int main() {
	
    size_t visitors_n;
    std::cin >> visitors_n;
		
	Pair*  visitors = new Pair[visitors_n];
	
    for (int i = 0; i < visitors_n; i++) {
        int a, b;
        std::cin >> a >> b;
		visitors[i] = Pair(a, b);
    }
	
	merge_sort(visitors, visitors_n);
	
	int times = 2;

    int end = visitors[0].leave;
    int start = end - 1;
	
	for (int i = 1; i < visitors_n; i++) {
		
        if (end <= visitors[i].leave && start >= visitors[i].come) 
		{
            continue;
        } 
		else if (end >= visitors[i].come) 
		{
            start = end;
            end = visitors[i].leave;
            times += 1;
        } 
		else  
		{
            end = visitors[i].leave;
            start = end - 1;
            times += 2;
        }
    }
	
	std::cout<<times;
	
    return 0;
}
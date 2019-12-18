/*
5_4. Закраска прямой 2.
На числовой прямой окрасили N отрезков. Известны координаты левого и
правого концов каждого отрезка (Li и Ri). Найти сумму длин частей
числовой прямой, окрашенных ровно в один слой.
*/

#include <iostream>
#include <cstring>

using namespace std;


struct Line {
    int start;
    int finish;
    Line(): start(0), finish(0) {}
    Line(int x, int y) : start(x), finish(y) {}
};

template <class T, class Compare>
void merge(T* Left, size_t left_s, T* Right, size_t right_s, T* Result, Compare cmp)
{
	size_t l_i, r_i, res_i;
	l_i = 0;
	r_i = 0;
	res_i = 0;

	while (cmp(l_i, left_s) && cmp(r_i, right_s))
    {
      if (Left[l_i].start == Right[r_i].start ) {
        if (Left[l_i].finish < Right[r_i].finish) {
          Result[res_i].start = Left[l_i].start;
          Result[res_i].finish = Left[l_i].finish;
          l_i++;
        }
        else
        {
          Result[res_i].start = Right[r_i].start;
          Result[res_i].finish = Right[r_i].finish;
          r_i++;
        }
      }
      else if (Left[l_i].start < Right[r_i].start) {
        Result[res_i].start = Left[l_i].start;
        Result[res_i].finish = Left[l_i].finish;
        l_i++;
      }
      else
      {
        Result[res_i].start = Right[r_i].start;
        Result[res_i].finish = Right[r_i].finish;
        r_i++;
      }

		res_i++;

    }

	if (l_i == left_s)
	{
		while( r_i != right_s)
		{
			Result[res_i].start = Right[r_i].start;
			Result[res_i].finish = Right[r_i].finish;
			r_i++;
			res_i++;
		}
	}
	else
	{
		while( l_i != left_s)
		{
			Result[res_i].start = Left[l_i].start;
			Result[res_i].finish = Left[l_i].finish;
			l_i++;
			res_i++;
		}
	}
}


template <class T, class Compare>
void merge_sort(T* array, int size, Compare cmp)
{
  if (size <= 1){
    return;
  }

  size_t first = size / 2;
	size_t second = size - first;

  merge_sort( array, first, cmp);
  merge_sort( array + first, second, cmp);

  T*  tmp = new T[size];
  merge(array, first, array + first, second, tmp, cmp);

  memcpy(array, tmp, sizeof( T ) * size );
  delete[] tmp;

}


int main(int argc, char const *argv[]) {

  int N;
  cin >> N;

  Line* lines = new Line[N];


  for (size_t i = 0; i < N; i++) {

    int x, y;
    cin >> x >> y;
    lines[i] = Line(x, y);

  }

  merge_sort(lines, N,  [](const int& l, const int& r)  {return l < r;});

  int result = 0;
  int current_s = lines[0].start;
  int current_f = lines[0].finish;
  //двигаемся по массиву точек
  for (size_t i = 1; i < N; i++) {
    //новый отрезок не пересекается со старым
    if (lines[i].start >= current_f)
    {
      result += current_f;
      result -= current_s;

      current_s = lines[i].start;
      current_f = lines[i].finish;
    }
    else if (lines[i].start < current_s){
       if (lines[i].finish > current_s) {
       current_s = (current_f < lines[i].finish)? current_f : lines[i].finish;
       current_f = (current_f >= lines[i].finish)? current_f : lines[i].finish;
       }
   }
    else if ( lines[i].start < current_f ) {
        result += lines[i].start - current_s;

        if ( lines[i].finish < current_f) {
  				current_s =  lines[i].finish;
  			}
  			else {
  				current_s = current_f;
  				current_f =  lines[i].finish;
  			}
    }
  }

  result += current_f;
  result -= current_s;

  cout << result << '\n';

  return 0;
}

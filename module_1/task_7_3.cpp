/*Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел.
Количество чисел не больше 106. Отсортировать массив методом
MSD по битам (бинарный QuickSort).
*/
#include <iostream>
using namespace std;

#define MAXLEN 64

int get_digit(long long number, int digit)
{
    return (number >> digit & 1u);
}


void MSD(long long *array, long start, long finish, int digit)
{
  if (start >= finish || digit < 0){
    return; //конец сортировки
  }

  long i = start;
  long j = finish;

  //ищем, какие два числа поменять
  while (i < j){

    while (!get_digit(array[i], digit) && (i < j)) {
      i++;
    }

    while (get_digit(array[j], digit) && (i < j) ) {
      j--;
    }
     swap(array[i], array[j]);
  }

  if (!get_digit(array[finish], digit))
  {
    j++;
  }

  MSD(array, start, j - 1, digit - 1);
  MSD(array, j, finish, digit - 1 );

}

int main(int argc, char const *argv[]) {

  long size = 0;

  cin >> size;

  long long *array = new long long[size];

  for (long i = 0; i < size; i++) {
    cin >> array[i];
  }

  //максимум 64 разряда, от 0 до 63
  MSD(array, 0, size-1, 63);

  for (long i = 0; i < size; i++) {
    cout << array[i] << " ";
  }

  return 0;
}

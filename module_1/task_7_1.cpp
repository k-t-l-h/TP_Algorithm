//
// Created by ktlh on 10.03.2021.
//

/*
 * 7_1. MSD для строк.
 * Дан массив строк. Количество строк не больше 105.
 * Отсортировать массив методом поразрядной сортировки MSD по символам.
 * Размер алфавита - 256 символов. Последний символ строки = ‘\0’.
 */

#include <string>
#include <iostream>

#define ALPHABET 256
#define START_SIZE 16

using namespace std;

int get_digit(string str, int ch) {
  //строчки с \0 считаем самыми маленькими
  return str.size() > ch ? str[ch]: 0;
}

void MSD(string* arr, int size, int step, int max_step) {
  //шаг ноль, проверяем условия остановки
  //размер не будет равен 1 из-за проверки в конце
  if (step > max_step) {
    return;
  }
  //шаг первый, создаем карманы
  int* buckets = new int[ALPHABET];
  for (int i = 0; i < ALPHABET; ++i) {
    buckets[i] = 0;
  }
  //подсчитываем элементы в карманах
  for (int i = 0; i < size; ++i) {
    ++buckets[get_digit(arr[i], step)];
  }

  //если массив весь остортирован, то ничего не делаем
  if (buckets[0] == size) {
    delete[] buckets;
    return;
  }

  //формируем границы подмассивов для рекурсивной сортировки
  for (int i = 1; i < ALPHABET; ++i) {
    buckets[i] += buckets[i-1];
  }

  //сама сортировка
  //дополнительный массив для сортировки
  string *strings = new string[size];

  //переставляем слова
  for (int i = size-1; i >= 0; --i) {
    strings[--buckets[get_digit(arr[i], step)]] = arr[i];
  }

  //перенос отсортированного
  for (int i = 0; i < size; ++i) {
    arr[i] = strings[i];
  }

  delete[]strings;
  //сортируем каждый карман отдельно
  //MSD(arr, size, left, step+1, max_step);
  for (int i = 1; i < ALPHABET; ++i) {
    if (buckets[i] - buckets[i - 1] > 1) {
      MSD(arr + buckets[i - 1], buckets[i] - buckets[i - 1], step + 1, max_step);
    }
  }
  delete[] buckets;
}

int main(int argc, char const *argv[]) {
  string str;
  string *strings = new string[START_SIZE];
  int size = 0;
  int max_size = START_SIZE;
  int value = 0; //величина строки

  while(cin >> str) {
    strings[size] = str;
    value = value < str.size() ? str.size() : value;
    size++;

    if (max_size == size) {
      string *tmp = new string[max_size<<1];

      for (int i = 0; i < size; ++i) {
        tmp[i] = strings[i];
      }
      delete[]strings;

      strings =  tmp;
      max_size = max_size<<1;
    }
  }

  MSD(strings, size, 0, value);

  for (int i = 0; i < size; ++i) {
    cout << strings[i] << "\n";
  }
  delete[] strings;

  return 0;
}

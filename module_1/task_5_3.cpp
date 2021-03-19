//
// Created by ktlh on 10.03.2021.
//

/*
 * 5_3. Закраска прямой 1.
 * На числовой прямой окрасили N отрезков.
 * Известны координаты левого и правого концов каждого отрезка (Li и Ri).
 * Найти длину окрашенной части числовой прямой.
 */

#include <iostream>
#include <cstring>
using namespace std;

struct Line {
  int start;
  int end;
  Line(): start(0), end(0) {}
  Line(int start, int end): start(start), end(end) {}

};

struct LineComparator {
  bool operator() (const Line &A, const Line &B) {

    if (A.start < B.start) {
      return true;
    } else if (A.start == B.start) {
      if (A.end > B.end) {
        return false;
      }
      return true;
    } else {
      return false;
    }
  }

};

template<class T, class Comparator>
void merge(T* A, int a_size, T* B, int b_size, T* Result, Comparator cmp) {

  int iter_left, iter_right, iter_all = 0;

  while (iter_left < a_size && iter_right < b_size) {
    if (cmp(A[iter_left], B[iter_right])) {
      Result[iter_all] = A[iter_left];
      iter_left++;
    } else {
      Result[iter_all] = B[iter_right];
      iter_right++;
    }

    iter_all++;
  }

  if (iter_left == a_size) {
    while (iter_right != b_size) {
      Result[iter_all] = B[iter_right];
      iter_right++;
      iter_all++;
    }
  }

  if (iter_right == b_size) {
    while (iter_left != a_size) {
      Result[iter_all] = A[iter_left];
      iter_left++;
      iter_all++;
    }
  }
}

template<class T, class Comparator>
void merge_sort(T* array, int size, Comparator cmp){
  if (size <= 1) {
    return;
  }

  int left = 0, right = 0;
  left = size / 2;
  right = size - left;

  merge_sort( array, left, cmp);
  merge_sort( array + left, right, cmp);

  T* merged = new T[size];
  merge(array, left, array + left, right, merged, cmp);
  memcpy(array, merged, sizeof( T ) * size );
  delete[] merged;
}

int count(Line* lines, int size) {
  if (size == 0 || lines == nullptr) {
    return -1;
  }

  int colored = 0;
  //переменные для промежутков
  int start = lines[0].start, end = lines[0].end;

  for (int i = 1; i < size; ++i) {
        //если линии не пересекаются
        if (lines[i].start >= end) {
          colored += end - start;
          start = lines[i].start;
          end = lines[i].end;
        } else {
          //линии пересекаются, но всё ещё возможно два варианта
          if (lines[i].end > end) {
            colored += end - start;
            start = end;
            end = lines[i].end;
          }
        }
  }

  colored += end - start;

  return colored;
}


int main(int argc, char const *argv[]) {
  int N;
  cin >> N;

  Line* lines = new Line[N];

  for (int i = 0; i < N; i++) {

    int x, y;
    cin >> x >> y;
    lines[i] = Line(x, y);

  }

  merge_sort(lines, N, LineComparator());


  cout << count(lines, N);

  delete[] lines;

  return 0;
}

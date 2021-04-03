//Дан массив, который получен путем нескольких циклических 
//сдвигов исходного отсортированного массива. 
//Нужно найти индекс элемента, с которого начинался исходный массив.

#include <iostream>
#include <random>
#include <ctime>

using namespace std;

struct GE {
    bool operator()(const int& l, const int& r) { return l > r; }
};

int random_pivot( int l, int r)
{
    srand(time(NULL));
    return ( l + rand() % (r - l));
}


template <class Comparator>
int partition(int* arr, int start, int end, Comparator cmp) {
    int pivot = random_pivot(start, end);

    int value = arr[pivot];

    if (pivot != start){
        swap(arr[pivot], arr[start]);
        pivot = start;
    }


    //проход двух итераторов от конца к началу
    int i = end - 1;
    int j = end - 1;

    for (j; j > start; j--) {
        if (cmp(arr[j], value)) {
            if (j != i) {
                swap(arr[i], arr[j]);
            }
            i--;
        }
    }

    if (pivot != i) {
        swap(arr[i], arr[pivot]);
    }

    return i;
}

template <class Comparator>
void K_stat(int* array, int size, int k, Comparator cmp) {
    int start = 0;
    int end = size;

    int pivot = partition(array, start, end, cmp);

    while (pivot != k) {
        if (pivot > k) {
            end = pivot;
        } else {
            start = pivot + 1;
        }
        pivot = partition(array, start, end, cmp);
    }
}

int main(int argc, const char* argv[]) {
    int n, k;
    cin >> n;

    int* arr = new int[n];
    int* arr_res = new int[n];
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        arr_res[i] = arr[i];
    }
    k = 0;
    K_stat(arr, n, k, GE());
    for (int i = 0; i < n; ++i) {
        if (arr_res[i] == arr[k]) {
                cout << i;
                break;
            }
    }

    delete[] arr;
    delete[] arr_res;

    return 0;
}

//
// Created by ktlh on 10.03.2021.
//

#include <iostream>
using namespace std;

void first_max(long *A, long *B, unsigned int size, unsigned int* a_it, unsigned int* b_it)
{
    long sum = A[0] + B[0];

    unsigned int tmp_it = 0;

    for (unsigned int i = 0; i < size; i++)
    {
        if (A[tmp_it] < A[i])
        {
            tmp_it = i;
        }

        if ( A[tmp_it] + B[i] > sum)
        {
            *b_it = i;
            *a_it = tmp_it;
            sum = A[*a_it] + B[*b_it];
        }

    }
}


int main()
{

    unsigned int size = 0;

    cin >> size;
    long *A = new long[size];

    for (unsigned int i = 0; i < size; i++)
    {
        cin >> A[i];
    }

    long *B = new long[size];

    for (unsigned int i = 0; i < size; i++)
    {
        cin >> B[i];
    }


    unsigned int a_it = 0;
    unsigned int b_it = 0;


    first_max(A, B, size, &a_it, &b_it);


    cout << a_it << " " << b_it;

    delete[] A;
    delete[] B;

    return 0;
}

//
// Created by Maryam Baig on 30/12/23.
//

#ifndef SEARCH_ENGINE_SORTING_H
#define SEARCH_ENGINE_SORTING_H
#include <iostream>
#include <vector>
#include <cstdlib>  // for rand
using namespace std;
template <class Comparable>
vector<Comparable> insertionSort2 (vector <Comparable> & a)
{
    int j;
    for (int p = 1;  p < a.size(); p++)
    {
        Comparable tmp = a[p];
        for (j = p; j > 0 &&  tmp.word < a[j-1].word; j--)
            a[j] = a[j-1];
        a[j] = tmp;
    }
    return a;
}
template <class Comparable>
void insertionSort (vector <Comparable> & a)
{
    int j;
    for (int p = 1;  p < a.size(); p++)
    {
        Comparable tmp = a[p];
        for (j = p; j > 0 &&  tmp.word < a[j-1].word; j--)
        a[j] = a[j-1];
        a[j] = tmp;
    }
}
template <class Comparable>
void percDown(vector<Comparable>& vector, int i, int n) {
    int child;
    Comparable tmp;

    for (tmp = vector[i]; 2*i+1 < n; i = child) {
        child = 2*i+1;
        if (child != n-1 && vector[child].word < vector[child+1].word) {
            child++;
        }

        if (vector[child].word > tmp.word) {
            vector[i] = vector[child];
        }
        else {
            break;
        }
    }

    vector[i] = tmp;
}

template <class Comparable>
void heapsort(vector<Comparable>& vector) {
    for (int i = vector.size()/2; i >=0; i--) {
        percDown(vector, i, vector.size());
    }

    for (int j = vector.size() -1; j >0; j--) {
        swap(vector[0], vector[j]);
        percDown(vector, 0, j);
    }
}

template <class Comparable>
void merge(vector<Comparable> &list, int start, int mid, int end)
{
    int start2 = mid + 1;

    // If the direct merge is already sorted
    if (list[mid].word <= list[start2].word) {
        return;
    }

    // Two pointers to maintain start
    // of both arrays to merge
    while (start <= mid && start2 <= end) {

        // If element 1 is in right place
        if (list[start].word <= list[start2].word) {
            start++;
        }
        else {
            Comparable value = list[start2];
            int index = start2;

            // Shift all the elements between element 1
            // element 2, right by 1.
            while (index != start) {
                list[index].word = list[index - 1].word;
                index--;
            }
            list[start] = value;

            // Update all the pointers
            start++;
            mid++;
            start2++;
        }
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
template <class Comparable>
void mergeSort(vector<Comparable> &list, int l, int r)
{
    if (l < r) {

        // Same as (l + r) / 2, but avoids overflow
        // for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(list, l, m);
        mergeSort(list, m + 1, r);

        merge(list, l, m, r);
    }
}

template <class Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;
    if ( a[ center ].word < a[ left ].word )
        swap( a[ left ], a[ center ] );
    if ( a[ right ].word < a[ left ].word )
        swap( a[ left ], a[ right ] );
    if ( a[ right ].word < a[ center ].word )
        swap( a[ center ], a[ right ] );

    // Place pivot at position right - 1
    swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}


template <class Comparable>
Comparable randomPivot(vector<Comparable>& vector, int left, int right) {
    // Implementation of random pivot selection
    int randomIndex = left + rand() % (right - left + 1);
    return vector[randomIndex];
}

template <class Comparable>
Comparable firstElementPivot(vector<Comparable>& vector,int left,int right) {
    // Implementation of using the first element as the pivot
    return vector[left];
}

/*template <class Comparable>
void quicksortWithPivot(vector<Comparable>& vector, int left, int right, Comparable (*pivotStrategy)(vector<Comparable>&, int, int)) {
    if (left + 10 <= right) {
        Comparable pivot = pivotStrategy(vector, left, right);

        int i = left, j = right - 1;
        for ( ; ; )
        {
            while (vector[++i].word < pivot);

            while (pivot < vector[--j].word);

            if (i < j) {
                swap(vector[i], vector[j]);
            }
            else {
                break;
            }
        }

        swap(vector[i], vector[right - 1]);    // Restore pivot
        quicksortWithPivot(vector, left, i - 1, pivotStrategy);   // Sort small elements
        quicksortWithPivot(vector, i + 1, right, pivotStrategy);  // Sort large elements
    } else {
        insertionSort(vector, left, right);
    }
}*/

template <class Comparable>
void quicksortWithMedianPivot(std::vector<Comparable>& vector,int left,int right) {
    //quicksortWithPivot(vector, 0, vector.size() - 1, median3);
    //int left=0,right=vector.size() - 1;
    if (left + 10 <= right) {
        Comparable pivot = median3(vector, left, right);
        // Begin partitioning
        int i = left, j = right - 1;
        for ( ; ; )
        {
            while (vector[++i].word < pivot.word);

            while (pivot.word < vector[--j].word);

            if (i < j) {
                swap(vector[i], vector[j]);
            }
            else {
                break;
            }
        }
        swap(vector[i], vector[right - 1]);	  // Restore pivot
        quicksortWithMedianPivot(vector, left, i - 1);    // Sort small elements
        quicksortWithMedianPivot(vector, i + 1, right);   // Sort large elements
    }

    else {  // Do an insertion sort on the subarray
        insertionSort(vector);
    }
}

template <class Comparable>
void quicksortWithRandomPivot(std::vector<Comparable>& vector,int left,int right) {
    //quicksortWithPivot(vector, 0, vector.size() - 1, randomPivot);

    if (left + 10 <= right) {
        Comparable pivot = randomPivot(vector, left, right);
        // Begin partitioning
        int i = left, j = right - 1;
        for ( ; ; )
        {
            while (vector[++i].word < pivot.word);

            while (pivot.word < vector[--j].word);

            if (i < j) {
                swap(vector[i], vector[j]);
            }
            else {
                break;
            }
        }
        swap(vector[i], vector[right - 1]);	  // Restore pivot
        quicksortWithRandomPivot(vector, left, i - 1);    // Sort small elements
        quicksortWithRandomPivot(vector, i + 1, right);   // Sort large elements
    }

    else {  // Do an insertion sort on the subarray
        insertionSort(vector);
    }
}

template <class Comparable>
void quicksortWithFirstElementPivot(std::vector<Comparable>& vector,int left,int right) {
    //quicksortWithPivot(vector, 0, vector.size() - 1, firstElementPivot);
    //int left=0,right=vector.size() - 1;
    if (left + 10 <= right) {
        Comparable pivot = firstElementPivot(vector, left, right);
        // Begin partitioning
        int i = left, j = right - 1;
        for ( ; ; )
        {
            while (vector[++i].word < pivot.word);

            while (pivot.word < vector[--j].word);

            if (i < j) {
                swap(vector[i], vector[j]);
            }
            else {
                break;
            }
        }
        swap(vector[i], vector[right - 1]);	  // Restore pivot
        quicksortWithFirstElementPivot(vector, left, i - 1);    // Sort small elements
        quicksortWithFirstElementPivot(vector, i + 1, right);   // Sort large elements
    }

    else {  // Do an insertion sort on the subarray
        insertionSort(vector);
    }
}
template <class Comparable>
void quicksort(std::vector<Comparable>& vector) {
    quicksortWithMedianPivot(vector, 0, vector.size() - 1);
}
#endif //SEARCH_ENGINE_SORTING_H

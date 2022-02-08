#ifndef UNTITLED3_HEAPSORTING_H
#define UNTITLED3_HEAPSORTING_H
#include <string>
#include "heapnode.h"
#include "hashing.h"

#include <iostream>

template <class Type>
class heapSorting {
    public:
    void swap(heapnode& first, heapnode& second);
    void heapify(heapnode arry[], int n, int i);
    void heapSort(heapnode arry[], int n);
};


extern int counter;

template <class Type>
void heapSorting<Type>::swap(heapnode& first, heapnode& second) {
    std::string tempWord;
    int tempCount;

    tempWord = first.words;
    tempCount = first.count;
    first.words = second.words;
    second.words = tempWord;
    first.count = second.count;
    second.count = tempCount;
}
template <class Type>
void heapSorting<Type>::heapify(heapnode arry[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arry[left].count < arry[largest].count) {
        largest = left;
    }
    if (right < n && arry[right].count < arry[largest].count) {
        largest = right;
    }
    if (largest != i) {
        swap(arry[i], arry[largest]);
        heapify(arry, n, largest);
    }
}
template <class Type>
void heapSorting<Type>::heapSort(heapnode arry[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arry, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arry[0], arry[i]);
        heapify(arry, i, 0);
    }
}

#endif //UNTITLED3_HEAPSORTING_H

//
// Created by jakub on 22.03.2025.
//

#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "../enums/PivotType.h"
#include <iostream>

class QuickSort {
public:
    explicit QuickSort(PivotType pivotT);
    template <typename T> void sort(T* array, int left, int right); //left/right are indexes
    template <typename T> static bool verify(T* array, int size);
private:
    PivotType pivotType;

    template <typename T> void quickSort(T* array, int left, int right);
    template <typename T>
    static int partition(T* array, int left, int right, int pivot);
    [[nodiscard]] int pickPivot(int left, int right) const;
};



template<typename T>
void QuickSort::sort(T* array, const int left, const int right) {
    quickSort<T>(array, left, right);
}

template<typename T>
int QuickSort::partition(T* array, const int left, int right, int pivot) {
    int j = left; //swap index
    std::swap(array[pivot], array[right]); //move pivot to right
    pivot = right;

    for (int i = left; i < right; i++) {
        if (array[i] <= array[pivot]) {
            std::swap(array[i], array[j]);
            j++;
        }
    }
    std::swap(array[j], array[pivot]); //move pivot
    return j;
}

template<typename T>
void QuickSort::quickSort(T* array, const int left, const int right) {
    if (left < right) {
        int pivot = pickPivot(left, right);
        if (pivot == -1) {
            std::cout<<"PIVOT ERROR"<<std::endl;
            return;
        }
        pivot = partition<T>(array, left, right, pivot);
        quickSort<T>(array, left, pivot-1);
        quickSort<T>(array, pivot+1, right);
    }
}

template <typename T>
bool QuickSort::verify(T* array, const int size) {
    for (int i = 1; i < size; i++) {
        if (array[i] < array[i - 1])
            return false;
    }
    return true;
}

#endif //QUICKSORT_H

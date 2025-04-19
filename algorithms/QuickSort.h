//
// Created by jakub on 22.03.2025.
//

#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "../enums/PivotType.h"
#include <random>


template <typename T>
class QuickSort {
public:
    QuickSort(T* array, int size, PivotType pivotT);
    void sort(); //left/right are indexes
    bool verify();
private:
    void quickSort(int left, int right);
    int partition(int left, int right, int pivot);
    [[nodiscard]] int pickPivot(int left, int right);

    PivotType pivotType;
    T* array;
    int size;
    std::random_device rd;
    std::mt19937 gen;
};

#include "QuickSort.tpp"
#endif //QUICKSORT_H
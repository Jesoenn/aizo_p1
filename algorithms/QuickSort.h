//
// Created by jakub on 22.03.2025.
//

#ifndef QUICKSORT_H
#define QUICKSORT_H
#include "../enums/PivotType.h"


template <typename T>
class QuickSort {
public:
    QuickSort(T* array, int size, PivotType pivotT);
    void sort(); //left/right are indexes
    bool verify();
private:
    void quickSort(int left, int right);
    int partition(int left, int right, int pivot);
    [[nodiscard]] int pickPivot(int left, int right) const;

    PivotType pivotType;
    T* array;
    int size;
};

#endif //QUICKSORT_H
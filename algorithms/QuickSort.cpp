//
// Created by jakub on 22.03.2025.
//

#include "QuickSort.h"
#include <iostream>
#include <random>


template<typename T>
QuickSort<T>::QuickSort(T *array, int size, PivotType pivotT) {
    this->array = array;
    this->size = size;
    this->pivotType = pivotT;
}

template<typename T>
void QuickSort<T>::sort() {
    quickSort(0, size-1);
}

template<typename T>
int QuickSort<T>::partition(const int left, int right, int pivot) {
    int j = left;                                       //index where elements smaller or equal pivot are placed
    std::swap(array[pivot], array[right]);    //move pivot to right
    pivot = right;

    for (int i = left; i < right; i++) {                //for each element from min index to max index
        if (array[i] <= array[pivot]) {
            std::swap(array[i], array[j]);    //place arr[i] on j place (swap)
            j++;                                        //move swap index to next place
        }
    }
    std::swap(array[j], array[pivot]);        //move pivot to swap index
    return j;
}

template<typename T>
void QuickSort<T>::quickSort(const int left, const int right) {
    if (left < right) {
        int pivot = pickPivot(left, right);
        pivot = partition(left, right, pivot);
        quickSort(left, pivot-1);
        quickSort(pivot+1, right);
    }
}

template <typename T>
bool QuickSort<T>::verify() {
    for (int i = 1; i < size; i++) {
        if (array[i] < array[i - 1])
            return false;
    }
    return true;
}

template <typename T>
int QuickSort<T>::pickPivot(const int left, const int right) const {
    switch (pivotType) {
        case PivotType::LEFT: return left;
        case PivotType::RIGHT: return right;
        case PivotType::MIDDLE: return left + (right - left) / 2;;
        case PivotType::RANDOM: {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(left, right);
            return dist(gen);
        }
        default: throw std::runtime_error("Invalid pivot type in pickPivot()");
    }
}

template class QuickSort<int>;
template class QuickSort<float>;
template class QuickSort<double>;
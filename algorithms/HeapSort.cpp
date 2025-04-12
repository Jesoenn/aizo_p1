//
// Created by jakub on 27.03.2025.
//

#include "HeapSort.h"
#include <iostream>

template <typename T>
HeapSort<T>::HeapSort(T* arr, int size) {
    this->array = arr;
    this->size = size;
    this->heapSize = size;
}

template <typename T>
void HeapSort<T>::sort() {
    buildHeap();
    for (int i = size-1; i >= 1; i--) {
        std::swap(array[0], array[i]);  //put largest element last in heap
        heapSize--;                               //decrement heap size
        heapify(0);                             //heapify from 0, because it was max element changed
    }
}

template<typename T>
void HeapSort<T>::buildHeap() {
    //heapify from second last row
    for (int i=size/2-1; i>=0; i--) { //-1 because index from 0, not 1
        heapify(i);
    }
}

//maintaining heap properties
template <typename T>
void HeapSort<T>::heapify(int i) {
    int largest=i;
    int leftChild = 2*i+1;
    int rightChild = 2*i+2;
    //Searching for largest child value. In case of swap, heapify again
    if (leftChild < heapSize && array[leftChild] > array[largest]) {
        largest = leftChild;
    }
    if (rightChild < heapSize && array[rightChild] > array[largest]) {
        largest = rightChild;
    }
    if (largest != i) {
        std::swap(array[i], array[largest]);
        heapify(largest);
    }
}

template <typename T>
bool HeapSort<T>::verify() {
    for (int i = 1; i < size; i++) {
        if (array[i] < array[i - 1])
            return false;
    }
    return true;
}

template class HeapSort<int>;
template class HeapSort<float>;
template class HeapSort<double>;
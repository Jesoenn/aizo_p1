//
// Created by jakub on 27.03.2025.
//

#ifndef HEAPSORT_H
#define HEAPSORT_H

template <typename T>
class HeapSort {
public:
    HeapSort(T* arr, int size);
    void sort();
    bool verify();
private:
    void buildHeap();
    void heapify(int i);

    T* array;
    int size,heapSize;
};

#endif //HEAPSORT_H

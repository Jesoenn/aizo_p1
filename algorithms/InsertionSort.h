//
// Created by jakub on 27.03.2025.
//

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H


template <typename T>
class InsertionSort {
public:
    InsertionSort(T* arr, int size);
    void sort();
    bool verify();
private:
    T* array;
    int arrSize;
};

#endif //INSERTIONSORT_H

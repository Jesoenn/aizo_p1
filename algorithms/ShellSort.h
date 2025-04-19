//
// Created by jakub on 27.03.2025.
//

#ifndef SHELLSORT_H
#define SHELLSORT_H

#include "../enums/ShellSequence.h"

template<typename T>
class ShellSort {
public:
    void sort();
    ShellSort(T* arr, int size, ShellSequence sequence);
    bool verify();
private:
    ShellSequence sequence;
    int gap;
    [[nodiscard]] int calcStartingGap() const;
    void declineGap();
    T* array;
    int arraySize;
};

#include "ShellSort.tpp"
#endif //SHELLSORT_H

//
// Created by jakub on 27.03.2025.
//

#pragma once
#include <iostream>

template<typename T>
void ShellSort<T>::sort() {
    while (gap > 0) {                               // while loop -> decreasing gaps until gap=1
        std::cout << "GAP: " << gap << std::endl;

        for (int i = gap; i < arraySize; i++) {     // insertion sort -> start from second element (gap)
            T key = array[i];                       // element to "sort"
            int j = i - gap;                        // previous element from key

            while (j >= 0 && array[j] > key) {      // move elements bigger than key to the right
                array[j + gap] = array[j];
                j -= gap;
            }
            array[j + gap] = key;                   // j + gap because j is decreased (place key in "empty" spot)
        }
        declineGap();                               // after using gap for each element in array, lower the gap
    }
}

template<typename T>
void ShellSort<T>::declineGap() {
    if (sequence==ShellSequence::NORMAL) {
        gap = gap/2;
    } else if (sequence == ShellSequence::KNUTH) {
        gap = (gap-1)/3;
    }
}


template<typename T>
ShellSort<T>::ShellSort(T* arr, int size, ShellSequence sequence) {
    this->array = arr;
    this->arraySize = size;
    this->sequence = sequence;
    gap=calcStartingGap();
}

template<typename T>
int ShellSort<T>::calcStartingGap() const {
    if (sequence==ShellSequence::NORMAL) {      // For normal sequence starting gap = n/2
        return arraySize/2;
    }
    int tempGap=1;
    while (tempGap*3+1 < arraySize/2) {         // For Knuth sequence, starting gap = 1, 4, 13, 40, ...
        tempGap = tempGap*3+1;
    }
    return tempGap;
}

template <typename T>
bool ShellSort<T>::verify() {
    for (int i = 1; i < arraySize; i++) {
        if (array[i] < array[i - 1])
            return false;
    }
    return true;
}

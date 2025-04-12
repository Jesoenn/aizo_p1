//
// Created by jakub on 27.03.2025.
//

#include "InsertionSort.h"

template <typename T>
InsertionSort<T>::InsertionSort(T* arr, int size) {
    this->array = arr;
    this->arrSize = size;
}

template <typename T>
void InsertionSort<T>::sort(){
    for(int i=1; i<arrSize; i++) {      // For each element in array starting from second
        T key = array[i];               // Pick it as key
        int j = i-1;
        while(j>=0 && array[j]>key){    // Compare key and move bigger elements to the right of array (it can occupy key index)
            array[j+1]=array[j];
            j--;                        //loop from index lower than key to 0
        }
        array[j+1]=key;                 //j+1 because j is decreased (place key in "empty" spot)
    }
}

template <typename T>
bool InsertionSort<T>::verify() {
    for (int i = 1; i < arrSize; i++) {
        if (array[i] < array[i - 1])
            return false;
    }
    return true;
}

template class InsertionSort<int>;
template class InsertionSort<float>;
template class InsertionSort<double>;
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

template <typename T>
InsertionSort<T>::InsertionSort(T* arr, int size) {
    this->array = arr;
    this->arrSize = size;
}

template <typename T>
void InsertionSort<T>::sort(){
    for(int i=1; i<arrSize; i++) {
        T key = array[i];
        int j = i-1;
        while(j>=0 && array[j]>key){    //move elements bigger than key to the right of array
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
#endif //INSERTIONSORT_H

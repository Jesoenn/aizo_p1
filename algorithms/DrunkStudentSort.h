//
// Created by jakub on 27.03.2025.
//

#ifndef DRUNKSTUDENTSORT_H
#define DRUNKSTUDENTSORT_H
#include <iostream>
#include <random>

template <typename T>
class DrunkStudentSort {
public:
    DrunkStudentSort(T* array, int size, double drunkLevel);
    void sort();
    void insertionSort();
    bool verify();

private:
    double drunkLevel; //from 0-1 (1 -> 100% error)
    T* array;
    int arrSize;
};

template<typename T>
DrunkStudentSort<T>::DrunkStudentSort(T *array, int size, double drunkLevel) {
    this->array = array;
    this->drunkLevel = drunkLevel;
    this->arrSize = size;
}

template <typename T>
void DrunkStudentSort<T>::sort() {
    //repeat until values are sorted correctly
    do {
        insertionSort();
    }while (!verify());
}

template <typename T>
void DrunkStudentSort<T>::insertionSort(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0, 1);
    for(int i=1; i<arrSize; i++) {
        if (dis(gen) < drunkLevel) { //chance to skip taking element as key
            continue;
        }
        T key = array[i];
        int j = i-1;
        while(j>=0 && array[j]>key){ //move elements bigger than key to the right
            array[j+1]=array[j];
            j--;
        }
        array[j+1]=key; //j+1 because j is decreased
    }
}

template <typename T>
bool DrunkStudentSort<T>::verify() {
    for (int i = 1; i < arrSize; i++) {
        if (array[i] < array[i - 1])
            return false;
    }
    return true;
}

#endif //DRUNKSTUDENTSORT_H

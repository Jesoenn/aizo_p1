//
// Created by jakub on 27.03.2025.
//
#pragma once

#include <random>

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
    for(int i=1; i<arrSize; i++) {      // For each element in array starting from second
        if (dis(gen) < drunkLevel) { //chance to skip taking element as key
            continue;
        }
        T key = array[i];               // pick "i" as key
        int j = i-1;
        while(j>=0 && array[j]>key){    // Compare key and move bigger elements to the right of array (it can occupy key index)
            array[j+1]=array[j];
            j--;                        //loop from index lower than key to 0
        }
        array[j+1]=key;                 //j+1 because j is decreased (place key in "empty" spot)
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
//
// Created by jakub on 27.03.2025.
//

#ifndef DRUNKSTUDENTSORT_H
#define DRUNKSTUDENTSORT_H

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

#endif //DRUNKSTUDENTSORT_H

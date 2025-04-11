//
// Created by jakub on 31.03.2025.
//

#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <iostream>

#include "../algorithms/InsertionSort.h"
#include "../core/FileManager.h"
#include "../core/Randomizer.h"
#include "../core/Timer.h"
#include "../algorithms/HeapSort.h"
#include "../enums/ShellSequence.h"
#include "../algorithms/ShellSort.h"
#include "../enums/PivotType.h"
#include "../algorithms/QuickSort.h"
#include "../algorithms/DrunkStudentSort.h"


class Benchmark {
public:
    Benchmark(int algorithm, int type, int size, int sorting, std::string outputFile,
             int algorithmType, double intoxication);
    void start();
private:
    template<typename T> void performSort();

    void initSortingType();
    void initAlgorithmTypeEnum();

    int algorithm,type,size,sorting,algorithmType;
    SortingType sortingType;
    AlgorithmType algorithmTypeEnum;
    std::string outputFile,chosenSortingType;
    double intoxication;
};

template<typename T>
void Benchmark::performSort() {
    initSortingType();                          //get sorting as enum
    initAlgorithmTypeEnum();                    //get algorithm as enum
    FileManager fileManager(outputFile);     //saving sorting data to files
    Randomizer randomizer;                      //fill array
    T* array = new T[size];
    Timer timer;

    T min, max;                                 // Determine min/max values based on type T
    if constexpr (std::is_integral_v<T>) {
        min = std::numeric_limits<T>::min();
        max = std::numeric_limits<T>::max();
    } else if constexpr (std::is_floating_point_v<T>) {
        min = std::numeric_limits<T>::lowest();
        max = std::numeric_limits<T>::max();
    }
    randomizer.fillArray(array,size,min,max,sortingType);



    std::cout<<"\n\nAlgorithm\tSize\tType\tTime [ms]\tSort Type\tCorrect?"<<std::endl;
    switch(algorithmTypeEnum) {
        case AlgorithmType::INSERTIONSORT: {
            InsertionSort<T> insertionSort(array, size);
            timer.start();
            insertionSort.sort();
            timer.stop();
            std::cout<<"Insertion\t"<<size<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
            <<"\t\tNONE\t\t"<<insertionSort.verify()<<std::endl;
            break;
        }
        case AlgorithmType::HEAPSORT: {
            HeapSort<T> heapSort(array,size);
            timer.start();
            heapSort.sort();
            timer.stop();
            std::cout<<"Heap\t\t"<<size<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\tNONE\t\t"<<heapSort.verify()<<std::endl;
            break;
        }
        case AlgorithmType::SHELLSORT: {
            ShellSequence sequence = ShellSequence::NORMAL;
            switch(algorithmType){
                case 0: sequence=ShellSequence::NORMAL; break;
                case 1: sequence=ShellSequence::KNUTH; break;
                default: std::cout<<"\nWrong algorithm type!"<<std::endl; break;
            }
            ShellSort<T> shellSort(array,size,sequence);
            timer.start();
            shellSort.sort();
            timer.stop();
            std::cout<<"Shell\t\t"<<size<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\t";
            if(sequence==ShellSequence::NORMAL) {
                std::cout<<"NORMAL";
            } else {
                std::cout<<"KNUTH";
            }
            std::cout<<"\t\t"<<shellSort.verify()<<std::endl;
            break;
        }
        case AlgorithmType::QUICKSORT: {
            PivotType pivotType = PivotType::RIGHT;
            switch(algorithmType){
                case 0: pivotType = PivotType::LEFT; break;
                case 1: pivotType = PivotType::RIGHT; break;
                case 2: pivotType = PivotType::MIDDLE; break;
                case 3: pivotType = PivotType::RANDOM; break;
                default: std::cout<<"\nWrong algorithm type!"<<std::endl; break;
            }
            QuickSort quickSort(pivotType);
            timer.start();
            quickSort.sort<T>(array,0,size-1);
            timer.stop();
            std::cout<<"Quick\t\t"<<size<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\t";
            if(pivotType==PivotType::LEFT) {
                std::cout<<"LEFT";
            } else if (pivotType==PivotType::RIGHT){
                std::cout<<"RIGHT";
            } else if (pivotType==PivotType::MIDDLE){
                std::cout<<"MIDDLE";
            } else {
                std::cout << "RANDOM";
            }
            std::cout<<"\t\t"<<quickSort.verify(array,size)<<std::endl;
            break;
        }
        case AlgorithmType::DRUNKSTUDENTSORT: {
            DrunkStudentSort<T> drunkStudentSort(array,size,intoxication);
            timer.start();
            drunkStudentSort.sort();
            timer.stop();
            std::cout<<"Student\t\t"<<size<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\t"<<intoxication<<"\t\t"<<drunkStudentSort.verify()<<std::endl;
            break;
        }
        default: std::cout<<"\nWrong algorithm!"<<std::endl; break;
    }

    //ZMIENIC ZAPIS ZEBY JESZCZE DOPISEK O PIVOCIE, ITD
    fileManager.saveData(algorithmTypeEnum,sortingType,typeid(T).name(),size,timer.result());
}

#endif //BENCHMARK_H

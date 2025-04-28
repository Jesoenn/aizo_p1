#pragma once
#include "../core/Timer.h"
#include "../algorithms/HeapSort.h"
#include "../enums/ShellSequence.h"
#include "../algorithms/ShellSort.h"
#include "../enums/PivotType.h"
#include "../algorithms/QuickSort.h"
#include "../algorithms/DrunkStudentSort.h"
#include "../algorithms/InsertionSort.h"
#include <iostream>

template<typename T>
void Benchmark::performSort() {
    initSortingType();                          //get sorting as enum
    initAlgorithmTypeEnum();                    //get algorithm as enum
    FileManager fileManager(outputFile, numbersFileName);     //saving sorting data to files
    Randomizer randomizer;                      // Data generator
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
    randomizer.fillArray(array,size,min,max,sortingType);   // Fill array
    std::cout<<"\nChosen sorting: "<<chosenSortingType;
    std::cout<<"\nAlgorithm\tSize\tType\tTime [ms]\tAlg Type\tCorrect?"<<std::endl;
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
            ShellSequence sequence;
            switch(algorithmType){
                case 0: sequence=ShellSequence::NORMAL; chosenAlgorithmType="NORMAL"; break;
                case 1: sequence=ShellSequence::KNUTH; chosenAlgorithmType="KNUTH"; break;
                default: throw std::runtime_error("Invalid algorithm type");
            }
            ShellSort<T> shellSort(array,size,sequence);
            timer.start();
            shellSort.sort();
            timer.stop();
            std::cout<<"Shell\t\t"<<size<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\t"<<chosenAlgorithmType<<"\t\t"<<shellSort.verify()<<std::endl;
            break;
        }
        case AlgorithmType::QUICKSORT: {
            PivotType pivotType;
            switch(algorithmType){
                case 0: pivotType = PivotType::LEFT; chosenAlgorithmType="LEFT"; break;
                case 1: pivotType = PivotType::RIGHT; chosenAlgorithmType="RIGHT"; break;
                case 2: pivotType = PivotType::MIDDLE; chosenAlgorithmType="MIDDLE"; break;
                case 3: pivotType = PivotType::RANDOM; chosenAlgorithmType="RANDOM"; break;
                default: throw std::runtime_error("Invalid algorithm type");
            }
            QuickSort<T> quickSort(array, size, pivotType);
            timer.start();
            quickSort.sort();
            timer.stop();
            std::cout<<"Quick\t\t"<<size<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\t"<<chosenAlgorithmType<<"\t\t"<<quickSort.verify()<<std::endl;
            break;
        }
        case AlgorithmType::DRUNKSTUDENTSORT: {
            DrunkStudentSort<T> drunkStudentSort(array,size,intoxication);
            timer.start();
            drunkStudentSort.sort();
            timer.stop();
            std::cout<<"Student\t\t"<<size<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\t"<<intoxication<<"\t\t"<<drunkStudentSort.verify()<<std::endl;
            chosenAlgorithmType=std::to_string(intoxication);
            const int dotIndex=static_cast<int>(chosenAlgorithmType.find('.'));
            chosenAlgorithmType[dotIndex]=',';
            chosenAlgorithmType=chosenAlgorithmType.substr(0,dotIndex+6);

            break;
        }
        default: throw std::runtime_error("Invalid algorithm");
    }
    fileManager.saveData(algorithmTypeEnum,sortingType,typeid(T).name(),size,timer.result(),chosenAlgorithmType);
    if(numbersFileName != "-"){
        fileManager.writeFile<T>(array, size);
    }
    delete[] array;
}
//
// Created by jakub on 31.03.2025.
//

#include "Benchmark.h"
#include "../core/Timer.h"
#include "../algorithms/HeapSort.h"
#include "../enums/ShellSequence.h"
#include "../algorithms/ShellSort.h"
#include "../enums/PivotType.h"
#include "../algorithms/QuickSort.h"
#include "../algorithms/DrunkStudentSort.h"
#include "../algorithms/InsertionSort.h"
#include <iostream>

Benchmark::Benchmark(const int algorithm, const int type, const int size, const int sorting, std::string outputFile,
             const int algorithmType, const double intoxication): sortingType(SortingType::NONE), algorithmTypeEnum(AlgorithmType::NONE) {
    this->algorithm = algorithm;
    this->type = type;
    this->size = size;
    this->sorting = sorting;
    this->outputFile = std::move(outputFile);
    this->algorithmType = algorithmType;
    this->intoxication = intoxication;
    this->chosenSortingType = "NULL";
}


void Benchmark::start() {
    switch (type) {
        case 0: {
            performSort<int>();
            break;
        }
        case 1: {
            performSort<float>();
            break;
        }
        case 2: {
            performSort<double>();
            break;
        }
        default: throw std::runtime_error("Invalid type");
    }
}

void Benchmark::initSortingType() {
    switch (sorting) {
        case 0: sortingType=SortingType::NONE; chosenSortingType="RANDOM"; break;
        case 1: sortingType=SortingType::ASCENDING; chosenSortingType="ASC"; break;
        case 2: sortingType=SortingType::DESCENDING; chosenSortingType="DESC"; break;
        case 3: sortingType=SortingType::PARTIALLY_33; chosenSortingType="PART_33"; break;
        case 4: sortingType=SortingType::PARTIALLY_66; chosenSortingType="PART_66"; break;
        default: throw std::runtime_error("Invalid sorting type");
    }
}

void Benchmark::initAlgorithmTypeEnum() {
    switch (algorithm) {
        case 0: algorithmTypeEnum = AlgorithmType::INSERTIONSORT; break;
        case 1: algorithmTypeEnum = AlgorithmType::HEAPSORT; break;
        case 2: algorithmTypeEnum = AlgorithmType::SHELLSORT; break;
        case 3: algorithmTypeEnum = AlgorithmType::QUICKSORT; break;
        case 4: algorithmTypeEnum = AlgorithmType::DRUNKSTUDENTSORT; break;
        default: throw std::runtime_error("Invalid algorithm");
    }
}

template<typename T>
void Benchmark::performSort() {
    initSortingType();                          //get sorting as enum
    initAlgorithmTypeEnum();                    //get algorithm as enum
    FileManager fileManager(outputFile);     //saving sorting data to files
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
    delete[] array;
}

template void Benchmark::performSort<int>();
template void Benchmark::performSort<float>();
template void Benchmark::performSort<double>();
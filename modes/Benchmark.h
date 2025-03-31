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
    switch(algorithm) {
        case 0: {
            InsertionSort<T> insertionSort(array, size);
            timer.start();
            insertionSort.sort();
            timer.stop();
            std::cout<<"Insertion\t"<<size<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
            <<"\t\tNONE\t\t"<<insertionSort.verify()<<std::endl;
            break;
        }
    }

    //ZMIENIC ZAPIS ZEBY JESZCZE DOPISEK O PIVOCIE, ITD
    fileManager.saveData(algorithmTypeEnum,sortingType,typeid(T).name(),size,timer.result());
}

#endif //BENCHMARK_H

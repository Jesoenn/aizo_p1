//
// Created by jakub on 31.03.2025.
//

#ifndef BENCHMARK_H
#define BENCHMARK_H
#include "../core/FileManager.h"
#include "../core/Randomizer.h"



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
    std::string outputFile,chosenSortingType,chosenAlgorithmType;
    double intoxication;
};

#include "Benchmark.tpp"
#endif //BENCHMARK_H
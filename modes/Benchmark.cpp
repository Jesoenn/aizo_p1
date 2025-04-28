//
// Created by jakub on 31.03.2025.
//

#include "Benchmark.h"
#include "../core/Timer.h"

Benchmark::Benchmark(const int algorithm, const int type, const int size, const int sorting, std::string outputFile, std::string numbersFile,
             const int algorithmType, const double intoxication): sortingType(SortingType::NONE), algorithmTypeEnum(AlgorithmType::NONE) {
    this->algorithm = algorithm;
    this->type = type;
    this->size = size;
    this->sorting = sorting;
    this->outputFile = std::move(outputFile);
    this->numbersFileName = std::move(numbersFile);
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
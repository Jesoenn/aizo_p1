//
// Created by jakub on 21.03.2025.
//

#include "FileManager.h"

#include <iomanip>
#include <utility>
#include <iostream>
#include <fstream>

FileManager::FileManager(std::string fileName)
    : inputFileName("NONE"), outputFileName("NONE"), dataFileName(std::move(fileName)) {}

FileManager::FileManager(std::string iFileName, std::string oFileName, std::string dataFileName)
    : inputFileName(std::move(iFileName)), outputFileName(std::move(oFileName)), dataFileName(std::move(dataFileName)) {}


int FileManager::getArrayLength() const {
    std::string input;
    std::ifstream file(inputFileName);

    if (!file.is_open()) {
        throw std::invalid_argument("Cannot open file");
    }
    std::getline(file, input);
    file.close();
    return std::stoi(input);
}

void FileManager::saveData(const AlgorithmType algorithm, const SortingType sorting, const std::string& variable, const int elements,
    const int time, const std::string& algorithmSettings) const {
    std::ofstream file(dataFileName, std::ios::app);

    // if (algorithm==AlgorithmType::DRUNKSTUDENTSORT) {
    //     const int dotIndex = algorithmSettings.find('.');
    //     algorithmSettings[dotIndex]=',';
    // }


    if (!file.is_open()) {
        std::cout << "Cannot open/create data file." << std::endl;
        return;
    }
    //Algorytm | Rodzaj algorytmu | Poczatkowe sortowanie | Typ zmiennej | Liczba elementow | Średni czas ms | Max czas | Min czas
    file << toString(algorithm) << "\t"
    << algorithmSettings << "\t"
    << toString(sorting) << "\t"
    << variable << "\t"
    << elements << "\t"
    << time << std::endl;

    file.close();
}

std::string FileManager::toString(const AlgorithmType algorithm) {
    switch (algorithm) {
        case AlgorithmType::QUICKSORT: return "QUICKSORT";
        case AlgorithmType::HEAPSORT: return "HEAPSORT";
        case AlgorithmType::SHELLSORT: return "SHELLSORT";
        case AlgorithmType::INSERTIONSORT: return "INSERTIONSORT";
        case AlgorithmType::DRUNKSTUDENTSORT: return "DRUNKSTUDENTSORT";
        default: return "ERROR";
    }
}

std::string FileManager::toString(const SortingType sorting) {
    switch (sorting) {
        case SortingType::NONE: return "NONE";
        case SortingType::ASCENDING: return "ASCENDING";
        case SortingType::DESCENDING: return "DESCENDING";
        case SortingType::PARTIALLY_33 : return "PARTIALLY_33";
        case SortingType::PARTIALLY_66 : return "PARTIALLY_66";
        default: return "ERROR";
    }
}

template<typename T> void FileManager::writeFile(T* array, const int arraySize) {
    std::ofstream file(outputFileName);
    file<<arraySize<<std::endl;
    for (int i=0; i<arraySize; i++) {
        file<<array[i]<<std::endl;
    }
    file.close();
}

template<typename T> T* FileManager::readFile() {
    std::string input;
    std::ifstream file(inputFileName);

    if (!file.is_open()) {
        std::cout << "Cannot open file. Array is empty" << std::endl;
        return nullptr;
    }

    std::getline(file, input);
    const int arrSize=std::stoi(input);

    T* array=new T[arrSize];

    for (int i=0;i<arrSize;i++) {
        std::getline(file, input);

        if constexpr(std::is_integral_v<T>) {
            array[i]=static_cast<T>(std::stoi(input));
        } else if constexpr (std::is_floating_point_v<T>){
            array[i]=static_cast<T>(std::stod(input));
        }
    }
    file.close();
    return array;
}



template void FileManager::writeFile<int>(int*, int);
template void FileManager::writeFile<float>(float*, int);
template void FileManager::writeFile<double>(double*, int);

template int* FileManager::readFile<int>();
template float* FileManager::readFile<float>();
template double* FileManager::readFile<double>();
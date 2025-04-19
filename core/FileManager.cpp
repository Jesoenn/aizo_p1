//
// Created by jakub on 21.03.2025.
//

#include "FileManager.h"
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
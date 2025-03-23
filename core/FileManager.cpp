//
// Created by jakub on 21.03.2025.
//

#include "FileManager.h"

#include <iomanip>
#include <utility>

FileManager::FileManager(std::string fileName)
    : inputFileName("NONE"), outputFileName("NONE"), dataFileName(std::move(fileName)) {}

FileManager::FileManager(std::string iFileName, std::string oFileName, std::string dataFileName)
    : inputFileName(std::move(iFileName)), outputFileName(std::move(oFileName)), dataFileName(std::move(dataFileName)) {}


int FileManager::getArrayLength() const {
    std::string input;
    std::ifstream file(inputFileName);

    if (!file.is_open()) {
        std::cout << "Cannot open file. Array is empty" << std::endl;
        return 0;
    }
    std::getline(file, input);
    file.close();
    return std::stoi(input);
}

void FileManager::saveData(const AlgorithmType algorithm, const SortingType sorting, const std::string& variable, const int elements, const int time) const {
    std::ofstream file(dataFileName, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Cannot open/create data file." << std::endl;
        return;
    }
    //Algorytm | Poczatkowe sortowanie | Typ zmiennej | Liczba elementow | Średni czas ms | Max czas | Min czas
    file << toString(algorithm) << "\t"
    << toString(sorting) << "\t"
    << variable << "\t"
    << elements << "\t"
    << time << std::endl;

    file.close();
}

std::string FileManager::toString(const AlgorithmType algorithm) {
    switch (algorithm) {
        case AlgorithmType::QUICKSORT: return "QUICKSORT";
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
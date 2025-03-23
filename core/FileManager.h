//
// Created by jakub on 21.03.2025.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <iostream>
#include <fstream>

#include "../enums/AlgorithmType.h"
#include "../enums/SortingType.h"


class FileManager {
private:
    const std::string inputFileName,outputFileName,dataFileName;

public:
    FileManager(std::string iFileName, std::string oFileName, std::string dataFileName);
    explicit FileManager(std::string fileName);
    [[nodiscard]] int getArrayLength() const;
    template<typename T> T* readFile();
    template<typename T> void writeFile(T* array, int arraySize); //For file test mode
    void saveData(AlgorithmType algorithm, SortingType sorting, const std::string& variable, int elements, int time) const;

    static std::string toString(AlgorithmType algorithm);
    static std::string toString(SortingType sorting);
};

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

template<typename T> void FileManager::writeFile(T* array, const int arraySize) {
    std::ofstream file(outputFileName);
    file<<arraySize<<std::endl;
    for (int i=0; i<arraySize; i++) {
        file<<array[i]<<std::endl;
    }
    file.close();
}

#endif //FILEMANAGER_H
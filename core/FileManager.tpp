//
// Created by jakub on 18.04.2025.
//
#pragma once
#include <iomanip>
#include <utility>
#include <iostream>
#include <fstream>

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
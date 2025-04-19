//
// Created by jakub on 21.03.2025.
//

#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>

#include "../enums/AlgorithmType.h"
#include "../enums/SortingType.h"


class FileManager {
public:
    FileManager(std::string iFileName, std::string oFileName, std::string dataFileName);
    explicit FileManager(std::string fileName);
    [[nodiscard]] int getArrayLength() const;
    template<typename T> T* readFile();
    template<typename T> void writeFile(T* array, int arraySize); //For file test mode
    void saveData(AlgorithmType algorithm, SortingType sorting, const std::string& variable, int elements, int time, const std::string& algorithmSettings) const;

    static std::string toString(AlgorithmType algorithm);
    static std::string toString(SortingType sorting);

private:
    const std::string inputFileName,outputFileName,dataFileName;
};

#include "FileManager.tpp"
#endif //FILEMANAGER_H
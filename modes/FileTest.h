//
// Created by jakub on 2025-03-31.
//

#ifndef AIZO_PROJEKT1_FILETEST_H
#define AIZO_PROJEKT1_FILETEST_H
#include "../core/FileManager.h"


class FileTest {
public:
    FileTest(int algorithm, int type,std::string inputFile,std::string outputFile,
             int algorithmType, double intoxication);
    void start();
private:
    template<typename T> void performSort();

    int algorithm,type,algorithmType;
    std::string inputFile,outputFile;
    double intoxication;
};

#include "FileTest.tpp"
#endif //AIZO_PROJEKT1_FILETEST_H

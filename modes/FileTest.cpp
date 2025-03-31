//
// Created by jakub on 2025-03-31.
//

#include "FileTest.h"
#include "../core/FileManager.h"
#include "../algorithms/InsertionSort.h"

#include <utility>

FileTest::FileTest(int algorithm, int type, std::string inputFile, std::string outputFile, int algorithmType,
                   double intoxication) {
    this->algorithm=algorithm;
    this->type=type;
    this->inputFile=std::move(inputFile);
    this->outputFile=std::move(outputFile);
    this->algorithmType=algorithmType;
    this->intoxication=intoxication;
}


void FileTest::start() {
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
        default: std::cout<<"\nWrong type!"<<std::endl; break;
    }
}

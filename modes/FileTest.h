//
// Created by jakub on 2025-03-31.
//

#ifndef AIZO_PROJEKT1_FILETEST_H
#define AIZO_PROJEKT1_FILETEST_H
#include <iostream>
#include "../algorithms/InsertionSort.h"
#include "../core/FileManager.h"
#include "../algorithms/HeapSort.h"
#include "../algorithms/ShellSort.h"
#include "../enums/PivotType.h"
#include "../algorithms/QuickSort.h"
#include "../algorithms/DrunkStudentSort.h"
#include "../core/Timer.h"

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

template<typename T>
void FileTest::performSort(){
    FileManager fileManager(inputFile,outputFile,"");
    T* array=fileManager.readFile<T>();
    const int arraySize=fileManager.getArrayLength();
    Timer timer;

    std::cout<<"\n\nAlgorithm\tSize\tType\tTime [ms]\tSort Type\tCorrect?"<<std::endl;
    switch(algorithm){
        case 0: {
            InsertionSort<T> insertionSort(array, arraySize);
            timer.start();
            insertionSort.sort();
            timer.stop();
            std::cout<<"Insertion\t"<<arraySize<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
            <<"\t\tNONE\t\t"<<insertionSort.verify()<<std::endl;
            break;
        }
        case 1: {
            HeapSort<T> heapSort(array,arraySize);
            timer.start();
            heapSort.sort();
            timer.stop();
            std::cout<<"Heap\t\t"<<arraySize<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\tNONE\t\t"<<heapSort.verify()<<std::endl;
            break;
        }
        case 2: {
            ShellSequence sequence = ShellSequence::NORMAL;
            switch(algorithmType){
                case 0: sequence=ShellSequence::NORMAL; break;
                case 1: sequence=ShellSequence::KNUTH; break;
                default: std::cout<<"\nWrong algorithm type!"<<std::endl; break;
            }
            timer.start();
            ShellSort<T> shellSort(array,arraySize,sequence);
            timer.stop();
            //WYSWIETLIC KNUTH LUB NORMAL
            std::cout<<"Shell\t\t"<<arraySize<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\t"<<"\t\t"<<shellSort.verify()<<std::endl;
            break;
        }
        case 3: {
            PivotType pivotType = PivotType::RIGHT;
            switch(algorithmType){
                case 0: pivotType = PivotType::LEFT; break;
                case 1: pivotType = PivotType::RIGHT; break;
                case 2: pivotType = PivotType::MIDDLE; break;
                case 3: pivotType = PivotType::RANDOM; break;
                default: std::cout<<"\nWrong algorithm type!"<<std::endl; break;
            }
            QuickSort quickSort(pivotType);
            quickSort.sort<T>(array,0,arraySize-1);
            std::cout<<"Czy wynik poprawny? "<<quickSort.verify(array,arraySize)<<std::endl;
            break;
        }
        case 4: {
            DrunkStudentSort<T> drunkStudentSort(array,arraySize,intoxication);
            drunkStudentSort.sort();
            std::cout<<"Czy wynik poprawny? "<<drunkStudentSort.verify()<<std::endl;
            break;
        }
        default: std::cout<<"\nWrong algorithm!"<<std::endl; break;
    }
    if(!outputFile.empty()){
        fileManager.writeFile<T>(array, arraySize);
    }
    delete[] array;
}

#endif //AIZO_PROJEKT1_FILETEST_H

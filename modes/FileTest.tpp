#pragma once
#include "../core/FileManager.h"
#include "../algorithms/HeapSort.h"
#include "../algorithms/ShellSort.h"
#include "../enums/PivotType.h"
#include "../algorithms/QuickSort.h"
#include "../algorithms/DrunkStudentSort.h"
#include "../core/Timer.h"
#include "../algorithms/InsertionSort.h"
#include <iostream>

template<typename T>
void FileTest::performSort(){
    FileManager fileManager(inputFile,outputFile,"");
    T* array=fileManager.readFile<T>();
    const int arraySize=fileManager.getArrayLength();
    Timer timer;

    std::cout<<"\n\nAlgorithm\tSize\tType\tTime [ms]\tAlg Type\tCorrect?"<<std::endl;
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
                default: throw std::runtime_error("Wrong algorithm type");
            }
            ShellSort<T> shellSort(array,arraySize,sequence);
            timer.start();
            shellSort.sort();
            timer.stop();
            std::cout<<"Shell\t\t"<<arraySize<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\t";
            if(sequence==ShellSequence::NORMAL) {
                std::cout<<"NORMAL";
            } else {
                std::cout<<"KNUTH";
            }
            std::cout<<"\t\t"<<shellSort.verify()<<std::endl;
            break;
        }
        case 3: {
            PivotType pivotType;
            switch(algorithmType){
                case 0: pivotType = PivotType::LEFT; break;
                case 1: pivotType = PivotType::RIGHT; break;
                case 2: pivotType = PivotType::MIDDLE; break;
                case 3: pivotType = PivotType::RANDOM; break;
                default: throw std::runtime_error("Wrong algorithm type");
            }
            QuickSort<T> quickSort(array,arraySize,pivotType);
            timer.start();
            quickSort.sort();
            timer.stop();
            std::cout<<"Quick\t\t"<<arraySize<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\t";
            if(pivotType==PivotType::LEFT) {
                std::cout<<"LEFT";
            } else if (pivotType==PivotType::RIGHT){
                std::cout<<"RIGHT";
            } else if (pivotType==PivotType::MIDDLE){
                std::cout<<"MIDDLE";
            } else {
                std::cout << "RANDOM";
            }
            std::cout<<"\t\t"<<quickSort.verify()<<std::endl;
            break;
        }
        case 4: {
            DrunkStudentSort<T> drunkStudentSort(array,arraySize,intoxication);
            timer.start();
            drunkStudentSort.sort();
            timer.stop();
            std::cout<<"Student\t\t"<<arraySize<<"\t"<<typeid(T).name()<<"\t"<<timer.result()
                     <<"\t\t"<<intoxication<<"\t\t"<<drunkStudentSort.verify()<<std::endl;
            break;
        }
        default: throw std::runtime_error("Wrong algorithm");
    }
    if(!outputFile.empty()){
        fileManager.writeFile<T>(array, arraySize);
    }
    delete[] array;
}
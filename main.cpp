
#include <iostream>

#include "algorithms/DrunkStudentSort.h"
#include "algorithms/HeapSort.h"
#include "algorithms/InsertionSort.h"
#include "algorithms/QuickSort.h"
#include "algorithms/ShellSort.h"
#include "core/FileManager.h"
#include "core/Randomizer.h"
#include "core/Timer.h"
#include <cmath>


double calcIntoxication(const double value, const double places) {
    return value/pow(10.0,places);
}

void callFileTest(const int algorithm, int type, const std::string& inputFile, const std::string& outputFile, int algorithmType, double intoxication) {
    FileManager fileManager(inputFile,outputFile,"");
    if ( algorithm == 0) {
        switch (type) {
            case 0:
                int* array=fileManager.readFile<int>();
                const int arraySize=fileManager.getArrayLength();
                InsertionSort<int> insertionSort(array, arraySize);
                insertionSort.sort();
                fileManager.writeFile<int>(array, arraySize);
                std::cout<<"Czy wynik poprawny?"<<insertionSort.verify()<<std::endl;
                delete[] array;
                break;
        }
    }
}

int main(const int argc, char* argv[]) {
    if (argc >1) {
        if (const std::string mode=argv[1]; mode == "--file") {
            std::cout<<"\nFILE TEST MODE:"<<std::endl;
            std::cout<<"\tUsage:"<<std::endl<<"\t  projekt1_aizo.exe --file <algorithm> <type> <inputFile> [outputFile] <alg type>"<<std::endl;
            std::cout<<"\n\t<algorithm>\tSorting algorithm to use (0 - Insertion, 1 - Heap, 2 - Shell, 3 - Quick, 4 - Drunk Student)."<<std::endl;
            std::cout<<"\t<type>\t\tData type to load (0 - int, 1 - float, 2 - double)."<<std::endl;
            std::cout<<"\t<inputFile>\tInput file containing the data to be sorted."<<std::endl;
            std::cout<<"\t[outputFile]\tIf provided, the sorted values will be saved to this file."<<std::endl;
            std::cout<<"\t<alg type>\tRequired algorithm specifics for:\n\t\t\t\tQuick Sort (PIVOT): 0 - Left, 1 - Right, 2 - Middle, 3 - Random"
                       "\n\t\t\t\tShell Sort (GAP): 0 - (n/2, n/8, ...), 1 - Knuth (1, 4 , 13, 40, ..., (3^k-1)/2)"
                       "\n\t\t\t\tDrunk Student (INTOXICATION): T<0.value> (0 -> 1)"<<std::endl;

            if (argc<5) {
                std::cout<<"\nWrong number of arguments."<<std::endl;
                return -2;
            }
            const int algorithm = std::stoi(argv[2]);
            const int type = std::stoi(argv[3]);
            const std::string inputFile = argv[4];
            //Optional arguments
            std::string outputFile;
            int algorithmType = -1;
            double intoxication = -1;
            if (argc == 7) {
                outputFile = argv[5];
                algorithmType = std::stoi(argv[6]);
                if (algorithmType == 4) {
                    intoxication = calcIntoxication(algorithmType,std::string(argv[6]).size());
                }
            } else if (algorithm>=2) {
                algorithmType = std::stoi(argv[5]);
                if (algorithmType == 4) {
                    intoxication = calcIntoxication(algorithmType,std::string(argv[5]).size());
                }
            } else if (argc == 6) {
                outputFile = argv[5];
            }
            callFileTest(algorithm, type, inputFile, outputFile, algorithmType, intoxication);
            return 0;
        } else if (mode == "--test") {
            //DODAC WYBOR CZY LOSOWO, ROSNACO, ITD WARTOSCI
            std::cout<<"\nBENCHMARK MODE:"<<std::endl;
            std::cout<<"\tUsage:"<<std::endl<<"\t  projekt1_aizo.exe ---test <algorithm> [alg type] <type> <size> <outputFile>"<<std::endl;
            std::cout<<"\n\t<algorithm>\tSorting algorithm to use (0 - Insertion, 1 - Heap, 2 - Shell, 3 - Quick, 4 - Drunk Student)."<<std::endl;
            std::cout<<"\t[alg type]\tAlgorithm specifics\n\t\t\t\tQuick Sort (PIVOT): 0 - Left, 1 - Right, 2 - Middle, 3 - Random"
                       "\n\t\t\t\tShell Sort (GAP): 0 - (n/2, n/8, ...), 1 - Knuth (1, 4 , 13, 40, ..., (3^k-1)/2)"
                       "\n\t\t\t\tDrunk Student (INTOXICATION): <double> (0 -> 1)"<<std::endl;
            std::cout<<"\t<type>\t\tData type to generate (0 - int, 1 - float, 2 - double)."<<std::endl;
            std::cout<<"\t<size>\t\tNumber of elements to generate (instance size)."<<std::endl;
            std::cout<<"\t<outputFile>\tFile where the benchmark results should be saved."<<std::endl;
            return 0;
        } else {
            std::cout<<std::endl<<"HELP MODE:"<<std::endl;
            std::cout<<"\tUsage:"<<std::endl<<"\tprojekt1_aizo.exe --help"<<std::endl;
            std::cout<<std::endl<<"EXAMPLE CALLS:"<<std::endl;
            std::cout<<"\tSorting integers using Heap Sort from a file and saving results:"<<std::endl;
            std::cout<<"\tprojekt1_aizo.exe --file 1 0 input.txt sorted_output.txt"<<std::endl<<std::endl;
            std::cout<<"\tRunning a benchmark with 1000 randomly generated floats using Insertion Sort:"<<std::endl;
            std::cout<<"\tprojekt1_aizo.exe --test 0 1 1000 results.txt"<<std::endl<<std::endl;
            return 0;
        }
    } else {
        std::cout<<"Use --help for more info"<<std::endl;
        return -1;
    }
}


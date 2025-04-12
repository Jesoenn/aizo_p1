
#include <iostream>

#include "algorithms/DrunkStudentSort.h"
#include "core/FileManager.h"
#include "core/Randomizer.h"
#include "core/Timer.h"
#include "modes/FileTest.h"
#include <cmath>
#include <random>

#include "modes/Benchmark.h"


double calcIntoxication(const double value, const double places) {
    return value/pow(10.0,places);
}

int main(const int argc, char* argv[]) {

    if (argc >1) {
        if (const std::string mode=argv[1]; mode == "--file") {
            if(argc<5){
                std::cout<<"\nFILE TEST MODE:"<<std::endl;
                std::cout<<"\tUsage:"<<std::endl<<"\t  projekt1_aizo.exe --file <algorithm> <type> <inputFile> [outputFile] <alg type>"<<std::endl;
                std::cout<<"\n\t<algorithm>\tSorting algorithm to use (0 - Insertion, 1 - Heap, 2 - Shell, 3 - Quick, 4 - Drunk Student)."<<std::endl;
                std::cout<<"\t<type>\t\tData type to load (0 - int, 1 - float, 2 - double)."<<std::endl;
                std::cout<<"\t<inputFile>\tInput file containing the data to be sorted."<<std::endl;
                std::cout<<"\t[outputFile]\tIf provided, the sorted values will be saved to this file."<<std::endl;
                std::cout<<"\t<alg type>\tRequired algorithm specifics for:\n\t\t\t\tQuick Sort (PIVOT): 0 - Left, 1 - Right, 2 - Middle, 3 - Random"
                           "\n\t\t\t\tShell Sort (GAP): 0 - (n/2, n/8, ...), 1 - Knuth (1, 4 , 13, 40, ..., (3^k-1)/2)"
                           "\n\t\t\t\tDrunk Student (INTOXICATION): T<0.value> (0 -> 1)"<<std::endl;
                return 0;
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
                if (algorithm == 4) {
                    intoxication = calcIntoxication(algorithmType,std::string(argv[6]).size());
                }
            } else if (algorithm>=2) {
                algorithmType = std::stoi(argv[5]);
                if (algorithm == 4) {
                    intoxication = calcIntoxication(algorithmType,std::string(argv[5]).size());
                }
            } else if (argc == 6) {
                outputFile = argv[5];
            }
            FileTest fileTest(algorithm, type, inputFile, outputFile, algorithmType, intoxication);
            fileTest.start();

            return 0;
        } else if (mode == "--test") {
            //DODAC WYBOR CZY LOSOWO, ROSNACO, ITD WARTOSCI
            if (argc < 7) {
                std::cout<<"\nBENCHMARK MODE:"<<std::endl;
                std::cout<<"\tUsage:"<<std::endl<<"\t  projekt1_aizo.exe ---test <algorithm> <type> <size> <sorting> <outputFile> <alg type>"<<std::endl;
                std::cout<<"\n\t<algorithm>\tSorting algorithm to use (0 - Insertion, 1 - Heap, 2 - Shell, 3 - Quick, 4 - Drunk Student)."<<std::endl;
                std::cout<<"\t<type>\t\tData type to generate (0 - int, 1 - float, 2 - double)."<<std::endl;
                std::cout<<"\t<size>\t\tNumber of elements to generate (instance size)."<<std::endl;
                std::cout<<"\t<sorting>\tStarting array order (0 - Random, 1 - Ascending, 2 - Descending, 3 - 1/3 sorted, 4 - 2/3 sorted)"<<std::endl;
                std::cout<<"\t<outputFile>\tFile where the benchmark results should be saved."<<std::endl;
                std::cout<<"\t<alg type>\tAlgorithm specifics\n\t\t\t\tQuick Sort (PIVOT): 0 - Left, 1 - Right, 2 - Middle, 3 - Random"
                           "\n\t\t\t\tShell Sort (GAP): 0 - (n/2, n/8, ...), 1 - Knuth (1, 4 , 13, 40, ..., (3^k-1)/2)"
                           "\n\t\t\t\tDrunk Student (INTOXICATION): T<0.value> (0 -> 1)"<<std::endl;
                return 0;
            }

            const int algorithm = std::stoi(argv[2]);
            const int type = std::stoi(argv[3]);
            const int size = std::stoi(argv[4]);
            const int sorting = std::stoi(argv[5]);
            const std::string outputFile = argv[6];
            //Optional arguments
            int algorithmType = -1;
            double intoxication = -1;
            if (argc == 8) {
                algorithmType = std::stoi(argv[7]);
                if (algorithm == 4) {
                    intoxication = calcIntoxication(algorithmType,std::string(argv[7]).size());
                }
            }

            Benchmark benchmark(algorithm,type,size,sorting,outputFile,algorithmType,intoxication);
            benchmark.start();

            return 0;
        } else {
            std::cout<<std::endl<<"HELP MODE:"<<std::endl;
            std::cout<<"\tUsage:"<<std::endl<<"\tprojekt1_aizo.exe --help"<<std::endl;
            std::cout<<std::endl<<"EXAMPLE CALLS:"<<std::endl;
            std::cout<<"\tSorting integers using Heap Sort from a file and saving results:"<<std::endl;
            std::cout<<"\tprojekt1_aizo.exe --file 1 0 input.txt sorted_output.txt"<<std::endl<<std::endl;
            std::cout<<"\tRunning a benchmark with 1000 randomly generated floats using Insertion Sort:"<<std::endl;
            std::cout<<"\tprojekt1_aizo.exe --test 0 1 1000 0 results.txt"<<std::endl<<std::endl;
            return 0;
        }
    } else {
        std::cout<<"Use --help for more info"<<std::endl;
        return -1;
    }
}

//TODO -  przerzucic templaty do osobnych plikow .cpp
//TODO - Dopisać do ostatecznego pliku funkcji test koncowa zmienna
//TODO - Zapewnic wywalanie errorów
//TODO - przeprowadzic male testy na plikach czy kazde sortowanie na 100% dziala


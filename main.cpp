#include <array>
#include <array>
#include <iostream>

#include "algorithms/QuickSort.h"
#include "core/FileManager.h"
#include "core/Randomizer.h"
#include "core/Timer.h"

int main() {

    int size = 10;
    float* arr=new float[size];
    // for (int i = 0; i < size; i++) {
    //     arr[i] = size-i;
    // }
    Randomizer rand;
    rand.fillArray(arr,size,-1000000.0f,1000000.0f,SortingType::NONE);

    // for (int i = 0; i < size; i++) {
    //     std::cout << arr[i] << ", ";
    // }

    QuickSort sort(PivotType::RANDOM);
    sort.sort(arr,0,size-1);
    std::cout << std::endl << "====================================================" << std::endl;
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << ", ";
    }

    //sprawdzenie
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) {
            std::cout<<std::endl<<"ERROR";
        }
    }


    //Zrobic FILE TEST MODE, BENCHMARK MODE, HELP MODE

    return 0;
}

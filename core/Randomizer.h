//
// Created by jakub on 21.03.2025.
//

#ifndef RANDOMIZER_H
#define RANDOMIZER_H


#include "../enums/SortingType.h"

class Randomizer {
public:
    template<typename T> void fillArray(T* array, int arraySize, T min, T max, SortingType sort);
};

#include "Randomizer.tpp"
#endif //RANDOMIZER_H
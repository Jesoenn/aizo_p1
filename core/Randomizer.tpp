//
// Created by jakub on 21.03.2025.
//
#pragma once
#include <algorithm>
#include <random>


template<typename T>
void Randomizer::fillArray(T *array, const int arraySize, T min, T max, const SortingType sort) {
    std::random_device rd;
    std::mt19937 gen(rd());

    if constexpr(std::is_integral_v<T>) {
        std::uniform_int_distribution<T> dis(min, max);
        for (int i = 0; i < arraySize; i++) {
            array[i] = dis(gen);
        }
    } else{
        std::uniform_real_distribution<long double> dis(min, std::nextafter(max, std::numeric_limits<T>::max()));
        for (int i = 0; i < arraySize; i++) {
            array[i] = dis(gen);
        }
    }

    if (sort == SortingType::ASCENDING) {
        std::sort(array, array + arraySize);
    } else if (sort == SortingType::DESCENDING) {
        std::sort(array, array + arraySize, std::greater<T>());
    } else if (sort == SortingType::PARTIALLY_33) {
        std::sort(array, array + arraySize/3);
    } else if (sort == SortingType::PARTIALLY_66) {
        std::sort(array, array + arraySize/3*2);
    }
}
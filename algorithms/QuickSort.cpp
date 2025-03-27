//
// Created by jakub on 22.03.2025.
//

#include "QuickSort.h"

#include <random>


QuickSort::QuickSort(const PivotType pivotT) {
    pivotType = pivotT;
}

int QuickSort::pickPivot(const int left, const int right) const {
    switch (pivotType) {
        case PivotType::LEFT: return left;
        case PivotType::RIGHT: return right;
        case PivotType::MIDDLE: return left + (right - left) / 2;;
        case PivotType::RANDOM: {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(left, right);
            return dist(gen);
        }
        default: return -1;
    }
}
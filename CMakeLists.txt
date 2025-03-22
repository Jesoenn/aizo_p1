cmake_minimum_required(VERSION 3.30)
project(projekt1_aizo)

set(CMAKE_CXX_STANDARD 26)

add_executable(projekt1_aizo main.cpp
        core/FileManager.cpp
        core/FileManager.h
        core/Timer.cpp
        core/Timer.h
        core/Randomizer.cpp
        core/Randomizer.h
        enums/SortingType.h
        enums/AlgorithmType.h
        algorithms/QuickSort.cpp
        algorithms/QuickSort.h)

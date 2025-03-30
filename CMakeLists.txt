cmake_minimum_required(VERSION 3.30)
project(projekt1_aizo)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(CMAKE_CXX_FLAGS "-static")

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
        algorithms/QuickSort.h
        enums/PivotType.h
        algorithms/InsertionSort.cpp
        algorithms/InsertionSort.h
        algorithms/HeapSort.cpp
        algorithms/HeapSort.h
        algorithms/DrunkStudentSort.cpp
        algorithms/DrunkStudentSort.h
        algorithms/ShellSort.cpp
        algorithms/ShellSort.h
        enums/ShellSequence.h
)

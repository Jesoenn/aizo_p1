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
        core/Randomizer.tpp
        core/Randomizer.h
        enums/SortingType.h
        enums/AlgorithmType.h
        algorithms/QuickSort.tpp
        algorithms/QuickSort.h
        enums/PivotType.h
        algorithms/InsertionSort.tpp
        algorithms/InsertionSort.h
        algorithms/HeapSort.tpp
        algorithms/HeapSort.h
        algorithms/DrunkStudentSort.tpp
        algorithms/DrunkStudentSort.h
        algorithms/ShellSort.tpp
        algorithms/ShellSort.h
        enums/ShellSequence.h
        modes/FileTest.cpp
        modes/FileTest.h
        modes/Benchmark.cpp
        modes/Benchmark.h
        core/FileManager.tpp
)

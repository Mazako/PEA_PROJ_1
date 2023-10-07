cmake_minimum_required(VERSION 3.25)
project(PEA_PROJ_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_PROJ_1 main.cpp
        PEA_UTILS/PeaUtils.cpp
        PEA_UTILS/PeaUtils.h
        TSP_MATRIX/TspMatrix.cpp
        TSP_MATRIX/TspMatrix.h BRUTE_FORCE/BruteForce.cpp BRUTE_FORCE/BruteForce.h)

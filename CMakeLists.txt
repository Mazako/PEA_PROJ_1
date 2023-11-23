cmake_minimum_required(VERSION 3.25)
project(PEA_PROJ_1)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)

include_directories(BRUTE_FORCE
        PEA_UTILS
        SHORTEST_PATH_RESULTS
        TSP_MATRIX
        TSP_MATRIX_SET
        SHORTEST_PATH_RESULTS/MULTIPLE_SHORTEST_PATH_MULTIPLE_RESULTS
        BRANCH_AND_BOUND_MATRIX_REDUCTION
        BRANCH_AND_BOUND_MATRIX_REDUCTION/REDUCED_TSP_MATRIX
        DYNAMIC_PROGRAMMING)

add_executable(PEA_PROJ_1 main.cpp
        PEA_UTILS/PeaUtils.cpp
        PEA_UTILS/PeaUtils.h
        TSP_MATRIX/TspMatrix.cpp
        TSP_MATRIX/TspMatrix.h
        BRUTE_FORCE/BruteForce.cpp
        BRUTE_FORCE/BruteForce.h
        TSP_MATRIX_SET/RandomTspMatrixSet.cpp
        TSP_MATRIX_SET/RandomTspMatrixSet.h
        SHORTEST_PATH_RESULTS/ShortestPathResults.cpp
        SHORTEST_PATH_RESULTS/ShortestPathResults.h
        SHORTEST_PATH_RESULTS/MULTIPLE_SHORTEST_PATH_MULTIPLE_RESULTS/MultipleShortestPathResults.cpp
        SHORTEST_PATH_RESULTS/MULTIPLE_SHORTEST_PATH_MULTIPLE_RESULTS/MultipleShortestPathResults.h
        BRANCH_AND_BOUND_MATRIX_REDUCTION/BranchAndBoundMatrixReduction.cpp
        BRANCH_AND_BOUND_MATRIX_REDUCTION/BranchAndBoundMatrixReduction.h
        BRANCH_AND_BOUND_MATRIX_REDUCTION/REDUCED_TSP_MATRIX/ReducedTspMatrix.cpp
        BRANCH_AND_BOUND_MATRIX_REDUCTION/REDUCED_TSP_MATRIX/ReducedTspMatrix.h
        DYNAMIC_PROGRAMMING/DynamicProgramming.cpp
        DYNAMIC_PROGRAMMING/DynamicProgramming.h )

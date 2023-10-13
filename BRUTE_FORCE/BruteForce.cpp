#include "BruteForce.h"
#include <iostream>

BruteForce::BruteForce() = default;

void
BruteForce::iteratePermutations(int n, int *array, std::function<void(int *)> iterateFunction, long timeLimitInMillis) {
    auto start = std::chrono::high_resolution_clock::now();
    auto c = new int[n];
    for (int i = 0; i < n; i++) {
        c[i] = 0;
    }
    iterateFunction(array);
    int i = 0;
    while (i < n) {
        if (c[i] < i) {
            if (i % 2 == 0) {
                PeaUtils::swap(0, i, array);
            } else {
                PeaUtils::swap(c[i], i, array);
            }
            iterateFunction(array);
            c[i]++;
            i = 0;
            auto current = std::chrono::high_resolution_clock::now();
            if (std::chrono::duration_cast<std::chrono::milliseconds>(current - start).count() > timeLimitInMillis) {
                throw std::invalid_argument("XD");
            }
        } else {
            c[i] = 0;
            i++;
        }
    }
}

ShortestPathResults *BruteForce::performShortestPath(TspMatrix *matrix, long timeLimitInMillis) {
    auto start = std::chrono::high_resolution_clock::now();
    int *minPath = nullptr;
    unsigned long long int lowestCost = INT64_MAX;
    auto shortestPathCalculator = [&minPath, &lowestCost, &matrix](int* path){
        unsigned long long cost = matrix->calculateCost(path);
        if (cost < lowestCost) {
            lowestCost = cost;
            delete[] minPath;
            minPath = PeaUtils::copyArray(matrix->getN(), path);
        }
    };
    try {
        int *permutationBase = PeaUtils::createArrayFromZeroToNMinusOne(matrix->getN());
        iteratePermutations(matrix->getN(),
                            permutationBase,
                            shortestPathCalculator,
                            timeLimitInMillis);
        auto end = std::chrono::high_resolution_clock::now();
        delete[] permutationBase;
        long long time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        return new ShortestPathResults(lowestCost,
                                       matrix->getN(),
                                       minPath,
                                       time);
    } catch (std::invalid_argument& invalid_argument) {
        std::cout << "Time limit exceded" << std::endl;
        return ShortestPathResults::createFailure();
    }
}

ShortestPathResults **BruteForce::performShortestPath(RandomTspMatrixSet *set, long timeLimitInMillis) {
    auto **results = new ShortestPathResults *[set->getN()];
    for (int i = 0; i < set->getN(); i++) {
        auto matrix = set->getMatrices()[i];
        std::cout << "MACIERZ: " << std::endl;
        std::cout << PeaUtils::matrixToString(matrix) << std::endl;
        auto result = performShortestPath(matrix, timeLimitInMillis);
        std::cout << result->toString() << std::endl;
        delete matrix;
        results[i] = result;
    }
    long double avgTime = PeaUtils::calculateAvgTime(set->getN(), results);
    std::cout << "Sredni wynik: " << std::to_string(avgTime)  << " ms"<< std::endl;
    return results;

}

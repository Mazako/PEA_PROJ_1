#include "BruteForce.h"
#include "MultipleShortestPathResults.h"
#include <iostream>

BruteForce::BruteForce() = default;

void BruteForce::iteratePermutations(int n, int *array, std::function<void(int *)> iterateFunction, long timeLimitInMillis) {
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
    unsigned long long lowestCost = 0;
    bool everFound = false;
    auto shortestPathCalculator = [&minPath, &lowestCost, &matrix, &everFound](int* path){
        unsigned long long cost = matrix->calculateCostThatExcludeZero(path);
        if (!everFound) {
            lowestCost = cost;
            everFound = true;
            minPath = PeaUtils::copyArray(matrix->getN() - 1, path);
        } else if (cost < lowestCost) {
            lowestCost = cost;
            delete[] minPath;
            minPath = PeaUtils::copyArray(matrix->getN() - 1, path);
        }
    };
    try {
        int *permutationBase = PeaUtils::createArrayFromOneToNMinusOne(matrix->getN());
        iteratePermutations(matrix->getN() - 1,
                            permutationBase,
                            shortestPathCalculator,
                            timeLimitInMillis);
        auto end = std::chrono::high_resolution_clock::now();
        delete[] permutationBase;
        long long time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        int *resultArr = new int[matrix->getN()];
        resultArr[0] = 0;
        for (int i = 1; i < matrix->getN(); i++) {
            resultArr[i] = minPath[i - 1];
        }
        delete minPath;
        return new ShortestPathResults(lowestCost,
                                       matrix->getN(),
                                       resultArr,
                                       time);
    } catch (std::invalid_argument& invalid_argument) {
        std::cout << "Time limit exceded" << std::endl;
        return ShortestPathResults::createFailure();
    }
}

MultipleShortestPathResults * BruteForce::performShortestPath(RandomTspMatrixSet *set, long timeLimitInMillis) {
    auto **results = new ShortestPathResults *[set->getN()];
    for (int i = 0; i < set->getN(); i++) {
        auto matrix = set->getMatrices()[i];
        auto result = performShortestPath(matrix, timeLimitInMillis);
        results[i] = result;
    }
    return MultipleShortestPathResults::createFromShortestPathResults(set->getN(), results);

}

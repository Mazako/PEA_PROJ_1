#include "BruteForce.h"
#include <iostream>
BruteForce::BruteForce() = default;

void BruteForce::iteratePermutations(int n, int *array, std::function<void(int *)> supplier) {
    int globalCounter = 0;
    int factorial = PeaUtils::factorial(n);
    auto c = new int[n];
    for (int i = 0; i < n; i++) {
        c[i] = 0;
    }
    supplier(array);
    int i = 0;
    while (i < n) {
        if (c[i] < i) {
            if (i % 2 == 0) {
                PeaUtils::swap(0, i, array);
            } else {
                PeaUtils::swap(c[i], i, array);
            }
            std::cout << globalCounter++ << " / " << factorial << std::endl;
            supplier(array);
            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
}

ShortestPathResults * BruteForce::performShortestPath(TspMatrix *matrix) {
    int *minPath = nullptr;
    unsigned long long int lowestCost = INT64_MAX;
    auto shortestPathCalculator = [&minPath, &lowestCost, &matrix](int* path){
        unsigned long long cost = matrix->calculateCost(path);
        if (cost < lowestCost) {
            lowestCost = cost;
            minPath = path;
        }
    };
    iteratePermutations(matrix->getN(), PeaUtils::createArrayFromZeroToNMinusOne(matrix->getN()), shortestPathCalculator);
    return new ShortestPathResults(lowestCost,
                                   matrix->getN(),
                                   PeaUtils::copyArray(matrix->getN(), minPath),
                                   0L);
}

ShortestPathResults **BruteForce::performShortestPath(RandomTspMatrixSet *set) {
    auto **results = new ShortestPathResults * [set->getN()];
    for (int i = 0; i < set->getN(); i++) {
        auto matrix = set->getMatrices()[i];
        auto result = performShortestPath(matrix);
        results[i] = result;
    }
    return results;

}

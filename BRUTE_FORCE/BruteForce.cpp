#include "BruteForce.h"
#include <iostream>
BruteForce::BruteForce() = default;

int ** BruteForce::createPermutation(int n, int *array) {
    auto allPermutations = new int *[PeaUtils::factorial(n)];
    int currentPos = 0;
    allPermutations[currentPos++] = PeaUtils::copyArray(n, array);
    auto c = new int[n];
    for (int i = 0; i < n; i++) {
        c[i] = 0;
    }
    int i = 0;
    while (i < n) {
        if (c[i] < i) {
            if (i % 2 == 0) {
                PeaUtils::swap(0, i, array);
            } else {
                PeaUtils::swap(c[i], i, array);
            }
            allPermutations[currentPos++] = PeaUtils::copyArray(n, array);
            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
    return allPermutations;
}

ShortestPathResults * BruteForce::performShortestPath(TspMatrix *matrix, int permutationLength, int **permutations) {
    int *minPath = nullptr;
    unsigned long long int lowestCost = INT64_MAX;
    for (int i = 0; i < permutationLength; i++) {
        unsigned long long int cost = matrix->calculateCost(permutations[i]);
        if (cost < lowestCost) {
            lowestCost = cost;
            minPath = permutations[i];
        }
    }
    return new ShortestPathResults(lowestCost,
                                   matrix->getN(),
                                   PeaUtils::copyArray(matrix->getN(), minPath),
                                   0L);
}

ShortestPathResults **BruteForce::performShortestPath(RandomTspMatrixSet *set) {
    auto **results = new ShortestPathResults * [set->getN()];
    auto permutations = createPermutation(set->getMatrixSize(), PeaUtils::createArrayFromZeroToNMinusOne(set->getMatrixSize()));
    int factorial = PeaUtils::factorial(set->getMatrixSize());
    for (int i = 0; i < set->getN(); i++) {
        auto matrix = set->getMatrices()[i];
        auto result = performShortestPath(matrix, factorial, permutations);
        results[i] = result;
    }
    return results;

}

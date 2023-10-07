#include "BruteForce.h"
#include <iostream>
BruteForce::BruteForce() = default;

std::vector<int *> BruteForce::createPermutation(int n, int *array) {
    auto allPermutations = std::vector<int*>();
    allPermutations.push_back(PeaUtils::copyArray(n, array));
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
            allPermutations.push_back(PeaUtils::copyArray(n, array));
            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
    return allPermutations;
}

ShortestPathResults * BruteForce::performShortestPath(TspMatrix *matrix) {
    auto permuations = createPermutation(matrix->getN(), PeaUtils::createArrayFromZeroToNMinusOne(matrix->getN()));
    int *minPath = nullptr;
    int lowestCost = INT32_MAX;
    for (const auto &path: permuations) {
        int cost = matrix->calculateCost(path);
        if (cost < lowestCost) {
            lowestCost = cost;
            minPath = path;
        }
    }
    return new ShortestPathResults(lowestCost,
                                   matrix->getN(),
                                   PeaUtils::copyArray(matrix->getN(), minPath),
                                   0L);
}

ShortestPathResults **BruteForce::performShortestPath(RandomTspMatrixSet *set) {
    auto **results = new ShortestPathResults * [set->getN()];
    return nullptr;

}

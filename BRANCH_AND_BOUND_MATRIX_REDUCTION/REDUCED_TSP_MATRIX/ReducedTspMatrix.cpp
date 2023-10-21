#include "ReducedTspMatrix.h"


unsigned long long int ReducedTspMatrix::getCost() const {
    return cost;
}

ReducedTspMatrix::ReducedTspMatrix(int n, int **matrix, unsigned long long int cost, const std::vector<int> &path)
        : TspMatrix(n, matrix), cost(cost), path(path) {}

const std::vector<int> &ReducedTspMatrix::getPath() const {
    return path;
}

int ReducedTspMatrix::getLastElementFromPath() {
    return path.back();
}

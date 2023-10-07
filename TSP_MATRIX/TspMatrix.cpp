#include "TspMatrix.h"

int TspMatrix::getN() const {
    return n;
}

int **TspMatrix::getMatrices() const {
    return matrix;
}

TspMatrix::~TspMatrix() {
    for (int i = 0; i < this->n; i++) {
        delete[] this->matrix[i];
    }
    delete[] this->matrix;
}

TspMatrix::TspMatrix(int n, int **matrix) {
    this->n = n;
    this->matrix = matrix;
}

unsigned long long int TspMatrix::calculateCost(int *path) {
    int first = path[0];
    int v1 = path[0];
    int v2;
    unsigned long long int totalCost = 0;
    for (int i = 1; i < this->n; i++) {
        v2 = path[i];
        totalCost += matrix[v1][v2];
        v1 = v2;
    }
    totalCost += matrix[v2][first];
    return totalCost;
}

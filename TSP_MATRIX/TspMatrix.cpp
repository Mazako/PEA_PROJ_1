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

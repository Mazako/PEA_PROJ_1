#include "RandomTspMatrixSet.h"

RandomTspMatrixSet::RandomTspMatrixSet(int n, int matrixSize) {
    this->n = n;
    this->matrixSize = matrixSize;
    this->matrices = new TspMatrix *[n];
    for (int i = 0; i < n; i++) {
        TspMatrix* matrix = PeaUtils::generateRandomTSPInstance(matrixSize);
        this->matrices[i] = matrix;
    }
}

RandomTspMatrixSet::~RandomTspMatrixSet() {
    for (int i = 0; i < this->n; i++) {
        delete this->matrices[i];
    }
    delete[] matrices;
}

TspMatrix **RandomTspMatrixSet::getMatrices() const {
    return matrices;
}

int RandomTspMatrixSet::getMatrixSize() const {
    return matrixSize;
}

int RandomTspMatrixSet::getN() const {
    return n;
}

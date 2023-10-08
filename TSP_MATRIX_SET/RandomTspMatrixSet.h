#ifndef PEA_PROJ_1_RANDOMTSPMATRIXSET_H
#define PEA_PROJ_1_RANDOMTSPMATRIXSET_H
#include "TspMatrix.h"
#include "PeaUtils.h"

class RandomTspMatrixSet {
private:
    TspMatrix **matrices;
    int matrixSize;
    int n;
public:
    RandomTspMatrixSet(int n, int matrixSize);
    ~RandomTspMatrixSet();

    TspMatrix **getMatrices() const;

    int getMatrixSize() const;

    int getN() const;
};


#endif //PEA_PROJ_1_RANDOMTSPMATRIXSET_H

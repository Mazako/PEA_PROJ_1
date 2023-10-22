#ifndef PEA_PROJ_1_REDUCEDTSPMATRIX_H
#define PEA_PROJ_1_REDUCEDTSPMATRIX_H


#include "TspMatrix.h"
#include "PeaUtils.h"

class ReducedTspMatrix : public TspMatrix{
private:
    unsigned long long cost;
    std::vector<int> path;
public:
    ReducedTspMatrix(int n, int **matrix, unsigned long long int cost, const std::vector<int> &path);

    unsigned long long int getCost() const;

    const std::vector<int> &getPath() const;

    int getLastElementFromPath();

    ReducedTspMatrix* copy();
};


#endif //PEA_PROJ_1_REDUCEDTSPMATRIX_H

#ifndef PEA_PROJ_1_TSPMATRIX_H
#define PEA_PROJ_1_TSPMATRIX_H

#include <vector>

class TspMatrix {
private:
    int n;
    int **matrix;
public:
    TspMatrix(int n, int **matrix);

    ~TspMatrix();

    int getN() const;

    int **getMatrices() const;

    unsigned long long int calculateCost(const int* path);
    unsigned long long int calculateCostThatExcludeZero(const int* path);
};


#endif //PEA_PROJ_1_TSPMATRIX_H

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

    int calculateCost(int* path);
};


#endif //PEA_PROJ_1_TSPMATRIX_H

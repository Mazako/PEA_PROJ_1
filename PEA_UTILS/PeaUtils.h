#ifndef PEA_PROJ_1_PEAUTILS_H
#define PEA_PROJ_1_PEAUTILS_H

#include <string>
#include <random>
#include <functional>
#include "../TSP_MATRIX/TspMatrix.h"

class PeaUtils {
private:
    PeaUtils();

public:
    static void swap(int i, int j, int *array);

    static int randomInt();

    static TspMatrix *generateRandomTSPInstance(int n);

    static std::string matrixToString(TspMatrix *tspMatrix);

    static void iterateMatrix(TspMatrix *tspMatrix, std::function<void(int, int, int)> function);
};


#endif //PEA_PROJ_1_PEAUTILS_H

#ifndef PEA_PROJ_1_PEAUTILS_H
#define PEA_PROJ_1_PEAUTILS_H

#include <string>
#include <random>
#include <functional>
#include <fstream>
#include <sstream>
#include "TspMatrix.h"
#include "ShortestPathResults.h"

class PeaUtils {
private:
    PeaUtils();

public:
    static void swap(int i, int j, int *array);

    static int *copyArray(int n, const int *array);

    static int **copyMatrix(int n, int **matrix);

    static int minimum(int n, const int *array);

    static int minimumColumn(int n, int **matrix, int column);

    static int *createArrayFromZeroToNMinusOne(int n);

    static int *createArrayFromOneToNMinusOne(int n);

    static std::vector<int> createVectorFromZeroToNMinusOne(int n);

    static int randomInt();

    static TspMatrix *generateRandomTSPInstance(int n);

    static std::string matrixToString(TspMatrix *tspMatrix);

    static std::string arrayToString(int n, int *arr);

    static TspMatrix *readMatrixFromFile(const std::string &filename);

    static int factorial(int n);

    static long double calculateAvgTime(int resultCount, ShortestPathResults **results);

    static long double calculateStandardDeviation(int resultCount, ShortestPathResults ** results, long double avg);

    static long double calculateSuccessRate(int resultCount, ShortestPathResults **results);

    static std::vector<int> subtractVectors(std::vector<int> &v1, std::vector<int> &v2);

};


#endif //PEA_PROJ_1_PEAUTILS_H

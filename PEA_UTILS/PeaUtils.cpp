#include "PeaUtils.h"

void PeaUtils::swap(int i, int j, int *array) {
    int tmp = array[j];
    array[j] = array[i];
    array[i] = tmp;
}

int PeaUtils::randomInt() {
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<> distribution(0, INT32_MAX);
    return distribution(rng);
}

TspMatrix *PeaUtils::generateRandomTSPInstance(int n) {
    int **matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            if (i == j) {
                matrix[i][j] = -1;
            } else {
                if (j < i) {
                    while (matrix[i][j] == matrix[j][i]) {
                        matrix[i][j] = randomInt();
                    }
                }
                matrix[i][j] = randomInt();
            }
        }
    }
    return new TspMatrix(n, matrix);
}

std::string PeaUtils::matrixToString(TspMatrix *tspMatrix) {
    std::string str;
    for (int i = 0; i < tspMatrix->getN(); i++) {
        str.append(arrayToString(tspMatrix->getN(), tspMatrix->getMatrices()[i]));
        if (i != tspMatrix->getN() - 1) {
            str.append("\n");
        }
    }
    return str;
}

int *PeaUtils::copyArray(int n, const int *array) {
    int *newArr = new int[n];
    for (int i = 0; i < n; i++) {
        newArr[i] = array[i];
    }
    return newArr;
}

int *PeaUtils::createArrayFromZeroToNMinusOne(int n) {
    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
    return arr;
}

int *PeaUtils::createArrayFromOneToNMinusOne(int n) {
    int *arr = new int [n - 1];
    for (int i = 1; i < n; i++) {
        arr[i - 1] = i;
    }
    return arr;
}

TspMatrix *PeaUtils::readMatrixFromFile(const std::string &filename) {
    using namespace std;
    string line;
    fstream newFile;
    newFile.open(filename, ios::in);
    int count;
    newFile >> count;
    if (count <= 0) {
        throw invalid_argument("Too small length of array");
    }
    int **matrix = new int *[count];
    for (int i = 0; i < count; i++) {
        matrix[i] = new int[count];
        for (int j = 0; j < count; j++) {
            newFile >> matrix[i][j];
            if (i == j) {
                matrix[i][j] = -1;
            }
        }
    }
    return new TspMatrix(count, matrix);
}

int PeaUtils::factorial(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

std::string PeaUtils::arrayToString(int n, int *arr) {
    std::string str;
    for (int i = 0; i < n; i++) {
        str.append(std::to_string(arr[i]));
        if (i != n - 1) {
            str.append(" ");
        }
    }
    return str;
}

long double PeaUtils::calculateAvgTime(int resultCount, ShortestPathResults **results) {
    long long totalTime = 0.;
    int successCount = 0;
    for (int i = 0; i < resultCount; i++) {
        if (results[i]->isSuccess()) {
            successCount++;
            totalTime += results[i]->getNanoTime();
        }
    }

    if (successCount == 0) {
        return -1;
    }

    return (long double) totalTime / successCount;
}

int **PeaUtils::copyMatrix(int n, int **matrix) {
    int **newArray = new int *[n];
    for (int i = 0; i < n; i++) {
        newArray[i] = copyArray(n, matrix[i]);
    }
    return newArray;
}

int PeaUtils::minimum(int n, const int *array) {
    int minimum = array[0];
    if (minimum == -1) {
        minimum = array[1];
    }
    for (int i = 0; i < n; i++) {
        if (array[i] > -1 && array[i] < minimum) {
            minimum = array[i];
        }
    }
    return minimum;
}

int PeaUtils::minimumColumn(int n, int **matrix, int column) {
    int minimum = matrix[0][column];
    if (minimum == -1) {
        minimum = matrix[1][column];
    }
    for (int i = 1; i < n; i++) {
        if (matrix[i][column] > -1 && matrix[i][column] < minimum) {
            minimum = matrix[i][column];
        }
    }
    return minimum;
}

std::vector<int> PeaUtils::createVectorFromZeroToNMinusOne(int n) {
    std::vector<int> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
        v.push_back(i);
    }
    return v;
}

std::vector<int> PeaUtils::subtractVectors(std::vector<int> &v1, std::vector<int> &v2) {
    std::vector<int> result;
    for (const auto &item: v1) {
        if (std::find(v2.begin(), v2.end(), item) == v2.end()) {
            result.push_back(item);
        }
    }
    return result;
}

long double PeaUtils::calculateStandardDeviation(int resultCount, ShortestPathResults **results, long double avg) {
    long double total = .0;
    for (int i = 0; i < resultCount; i++) {
        total += std::pow(results[i]->getNanoTime() - avg, 2);
    }
    total = total / (resultCount - 1);
    return std::sqrt(total);
}

long double PeaUtils::calculateSuccessRate(int resultCount, ShortestPathResults **results) {
    int successes = 0;
    for (int i = 0; i < resultCount; i++) {
        if (results[i]->isSuccess()) {
            successes++;
        }
    }
    return (double) successes / resultCount;
}

PeaUtils::PeaUtils() = default;

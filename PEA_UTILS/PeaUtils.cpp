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

TspMatrix * PeaUtils::generateRandomTSPInstance(int n) {
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
    iterateMatrix(tspMatrix, [&str, &tspMatrix](int i, int j, int a) {
        str.append(std::to_string(a)).append("\t");
        if (j == tspMatrix->getN() - 1) {
            str.append("\n");
        }
    });
    return str;
}

void PeaUtils::iterateMatrix(TspMatrix *tspMatrix, std::function<void(int, int, int)> function) {
    for (int i = 0; i < tspMatrix->getN(); i++) {
        for (int j = 0; j < tspMatrix->getN(); j++) {
            function(i, j, tspMatrix->getMatrices()[i][j]);
        }
    }
}

PeaUtils::PeaUtils() = default;

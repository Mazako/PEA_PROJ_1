#include <iostream>
#include <cstring>
#include <fstream>
#include "PeaUtils.h"
#include "BruteForce.h"
#include "RandomTspMatrixSet.h"
#include "BranchAndBoundMatrixReduction.h"

using std::cout;
using std::endl;
const char* BRUTE_FORCE_ARG = "GENERATE_BRUTE";

void generateBruteForceData(int matrixSize, int count);

int main(int argc, char *argv[]) {
    if (argc != 1) {
        auto argument = argv[1];
        int matrixSize = atoi(argv[2]);
        int count = atoi(argv[3]);
        if (strcmp(argument, BRUTE_FORCE_ARG) == 0) {
            cout << "Starting program in brute_force data generation mode." << endl;
            generateBruteForceData(matrixSize, count);
        }
    } else {
        auto set = PeaUtils::generateRandomTSPInstance(15);
        auto results = BranchAndBoundMatrixReduction::solve(set, 1000000);
        cout << results->toString() << endl;
//        auto res2 = BruteForce::performShortestPath(set, 10000000);
//        cout << res2->toString() << endl;

    }

}

void generateBruteForceData(int matrixSize, int count) {
    std::ofstream file;
    file.open("brute_force_sample.txt");
    file << matrixSize << " " << count << endl << endl;
    auto set = new RandomTspMatrixSet(count, matrixSize);
    for (int i = 0; i < count; i++) {
        auto currMatrix = set->getMatrices()[i];
        file << PeaUtils::matrixToString(currMatrix) << endl;
        auto result = BruteForce::performShortestPath(currMatrix, 1000000);
        file << result->getCost() << ";" << PeaUtils::arrayToString(result->getN(), result->getPath()) << endl;
        if (i != count - 1) {
            file << endl;
        }
        delete result;
    }
    delete set;
    file.close();
}

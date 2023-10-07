#include <iostream>
#include "PEA_UTILS/PeaUtils.h"
#include "BRUTE_FORCE/BruteForce.h"
using std::cout;
using std::endl;

int main() {
    TspMatrix *matrix = PeaUtils::readMatrixFromFile("exampleMatrix");
    cout << PeaUtils::matrixToString(matrix);
    cout << BruteForce::performShortestPath(matrix)->toString();
}

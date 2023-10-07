#include <iostream>
#include "PEA_UTILS/PeaUtils.h"
#include "BRUTE_FORCE/BruteForce.h"
#include "TSP_MATRIX_SET/RandomTspMatrixSet.h"

using std::cout;
using std::endl;

int main() {
    auto set = new RandomTspMatrixSet(1, 5);
    auto results = BruteForce::performShortestPath(set);
    cout << results[0]->toString();
}

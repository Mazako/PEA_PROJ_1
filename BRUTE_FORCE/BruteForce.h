#ifndef PEA_PROJ_1_BRUTEFORCE_H
#define PEA_PROJ_1_BRUTEFORCE_H

#include <vector>
#include <functional>
#include "../PEA_UTILS/PeaUtils.h"
#include "../SHORTEST_PATH_RESULTS/ShortestPathResults.h"
#include "../TSP_MATRIX_SET/RandomTspMatrixSet.h"


class BruteForce {
private:
    BruteForce();

public:
    static void iteratePermutations(int n, int *array, std::function<void(int *)> supplier);

    static ShortestPathResults *
    performShortestPath(TspMatrix *matrix);

    static ShortestPathResults **performShortestPath(RandomTspMatrixSet* set);
};


#endif //PEA_PROJ_1_BRUTEFORCE_H

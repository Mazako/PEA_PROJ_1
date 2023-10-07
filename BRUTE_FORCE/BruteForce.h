#ifndef PEA_PROJ_1_BRUTEFORCE_H
#define PEA_PROJ_1_BRUTEFORCE_H

#include <vector>
#include "../PEA_UTILS/PeaUtils.h"
#include "../SHORTEST_PATH_RESULTS/ShortestPathResults.h"
#include "../TSP_MATRIX_SET/RandomTspMatrixSet.h"

class BruteForce {
private:
    BruteForce();

public:
    static std::vector<int *> createPermutation(int n, int *array);

    static ShortestPathResults *performShortestPath(TspMatrix *matrix);

    static ShortestPathResults **performShortestPath(RandomTspMatrixSet* set);
};


#endif //PEA_PROJ_1_BRUTEFORCE_H

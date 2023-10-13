#ifndef PEA_PROJ_1_BRUTEFORCE_H
#define PEA_PROJ_1_BRUTEFORCE_H

#include <vector>
#include <functional>
#include <chrono>
#include "PeaUtils.h"
#include "ShortestPathResults.h"
#include "RandomTspMatrixSet.h"
#include "MULTIPLE_SHORTEST_PATH_MULTIPLE_RESULTS/MultipleShortestPathResults.h"


class BruteForce {
private:
    BruteForce();

public:
    static void
    iteratePermutations(int n, int *array, std::function<void(int *)> iterateFunction, long timeLimitInMillis);

    static ShortestPathResults *
    performShortestPath(TspMatrix *matrix, long timeLimitInMillis);

    static MultipleShortestPathResults * performShortestPath(RandomTspMatrixSet *set, long timeLimitInMillis);
};


#endif //PEA_PROJ_1_BRUTEFORCE_H

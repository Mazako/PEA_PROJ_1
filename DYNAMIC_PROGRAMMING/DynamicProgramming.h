#ifndef PEA_PROJ_1_DYNAMICPROGRAMMING_H
#define PEA_PROJ_1_DYNAMICPROGRAMMING_H

#include "ShortestPathResults.h"
#include "TspMatrix.h"
#include "RandomTspMatrixSet.h"
#include "MultipleShortestPathResults.h"

class DynamicProgramming {
private:
    inline static unsigned long long **memo = nullptr;
    inline static int **memoPath = nullptr;

    static unsigned long long int step(TspMatrix *matrix, int vertex, int mask);

public:
    static ShortestPathResults *solve(TspMatrix *matrix, long timeLimitInMillis);
    static MultipleShortestPathResults *solve(RandomTspMatrixSet *set, long timeLimitInMillis);

};


#endif //PEA_PROJ_1_DYNAMICPROGRAMMING_H

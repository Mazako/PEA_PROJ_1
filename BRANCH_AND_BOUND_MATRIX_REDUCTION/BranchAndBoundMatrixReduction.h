#ifndef PEA_PROJ_1_BRANCHANDBOUNDMATRIXREDUCTION_H
#define PEA_PROJ_1_BRANCHANDBOUNDMATRIXREDUCTION_H
#include<queue>
#include "ShortestPathResults.h"
#include "TspMatrix.h"
#include "REDUCED_TSP_MATRIX/ReducedTspMatrix.h"
#include "PeaUtils.h"
#include "RandomTspMatrixSet.h"
#include "MultipleShortestPathResults.h"


enum BranchMode {DFS, LOW_COST};

class BranchAndBoundMatrixReduction {
private:
    static ReducedTspMatrix *reduceMatrix(int n,
                                          int **matrix,
                                          unsigned long long int parentReductionCost,
                                          std::function<std::vector<int>(void)> pathSupplier,
                                          int stepCost,
                                          int vertexFrom,
                                          int vertexTo);
public:
    static ShortestPathResults *solve(TspMatrix *matrix, long timeLimitInMillis, BranchMode branchMode);
    static MultipleShortestPathResults *solve(RandomTspMatrixSet *set, long timeLimitInMillis, BranchMode branchMode);
    static ShortestPathResults* solveLowCost(TspMatrix *matrix, long  timeLimitInMillis);
    static ShortestPathResults* solveDfs(TspMatrix *matrix, long  timeLimitInMillis);
};


#endif //PEA_PROJ_1_BRANCHANDBOUNDMATRIXREDUCTION_H

#include <chrono>
#include "BranchAndBoundMatrixReduction.h"

ShortestPathResults *BranchAndBoundMatrixReduction::solve(TspMatrix *matrix, long timeLimitInMillis) {
    auto start = std::chrono::high_resolution_clock::now();
    struct QueueComparator {
        bool operator()(const ReducedTspMatrix *a, ReducedTspMatrix *b) {
            return a->getCost() > b->getCost();
        }
    };

    std::vector<int> allVertices = PeaUtils::createVectorFromZeroToNMinusOne(matrix->getN());
    std::priority_queue<ReducedTspMatrix *, std::vector<ReducedTspMatrix *>, QueueComparator> queue;
    auto rootPath = reduceMatrix(matrix->getN(),
                                 PeaUtils::copyMatrix(matrix->getN(), matrix->getMatrices()),
                                 0,
                                 []() {
                                     std::vector<int> v;
                                     v.push_back(0);
                                     return v;
                                 },
                                 0,
                                 -1,
                                 -1);
    queue.push(rootPath);
    ReducedTspMatrix* current;
    do {
        current = queue.top();
        queue.pop();
        auto path = current->getPath();
        std::vector remainingVertices = PeaUtils::subtractVectors(allVertices, path);
        int lastElement = current->getLastElementFromPath();
        for (const auto &vertex: remainingVertices) {
            int **stepMatrix = PeaUtils::copyMatrix(current->getN(), current->getMatrices());
            auto reduced = reduceMatrix(current->getN(),
                                        stepMatrix,
                                        current->getCost(),
                                        [&current, &vertex]() {
                                            std::vector copy(current->getPath());
                                            copy.push_back(vertex);
                                            return copy;
                                        },
                                        current->getMatrices()[lastElement][vertex],
                                        lastElement,
                                        vertex);
            queue.push(reduced);
            auto currentTime = std::chrono::high_resolution_clock::now();

            if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start).count() > timeLimitInMillis) {
                return ShortestPathResults::createFailure();
            }
        }
        if (current->getPath().size() != matrix->getN()) {
            delete current;
        }
    } while (current->getPath().size() != matrix->getN());

    auto end = std::chrono::high_resolution_clock::now();
    while (!queue.empty()) {
        auto ref = queue.top();
        queue.pop();
        delete ref;
    }

    int* path = new int [matrix->getN()];
    for (int i = 0; i < matrix->getN(); i++) {
        path[i] = current->getPath()[i];
    }
    return new ShortestPathResults(current->getCost(),
                                   current->getN(),
                                   path,
                                   std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
}

ReducedTspMatrix *BranchAndBoundMatrixReduction::reduceMatrix(int n,
                                                              int **matrix,
                                                              unsigned long long int parentReductionCost,
                                                              std::function<std::vector<int>(void)> pathSupplier,
                                                              int stepCost,
                                                              int vertexFrom,
                                                              int vertexTo) {
    unsigned long long totalReduction = 0;
    if (vertexFrom >= 0 && vertexTo >= 0) {
        matrix[vertexTo][vertexFrom] = -1;
        for (int i = 0; i < n; i++) {
            matrix[vertexFrom][i] = -1;
            matrix[i][vertexTo] = -1;
        }
    }


    for (int i = 0; i < n; i++) {
        int minRow = PeaUtils::minimum(n, matrix[i]);
        if (minRow > 0) {
            totalReduction += minRow;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] > 0) {
                    matrix[i][j] -= minRow;
                }
            }
        }
    }


    for (int i = 0; i < n; i++) {
        int minCol = PeaUtils::minimumColumn(n, matrix, i);
        if (minCol > 0) {
            totalReduction += minCol;
            for (int j = 0; j < n; j++) {
                if (matrix[j][i] > 0) {
                    matrix[j][i] -= minCol;
                }
            }
        }
    }

    totalReduction += stepCost + parentReductionCost;
    return new ReducedTspMatrix(n, matrix, totalReduction, pathSupplier());
}

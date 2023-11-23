#include <chrono>
#include <iostream>
#include <stack>
#include "BranchAndBoundMatrixReduction.h"

ShortestPathResults *BranchAndBoundMatrixReduction::solve(TspMatrix *matrix, long timeLimitInMillis,
                                                          BranchMode branchMode) {
    if (branchMode == LOW_COST) {
        return solveLowCost(matrix, timeLimitInMillis);
    }
    else {
        return solveDfs(matrix, timeLimitInMillis);
    }
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
        matrix[vertexTo][0] = -1;
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

MultipleShortestPathResults * BranchAndBoundMatrixReduction::solve(RandomTspMatrixSet *set, long timeLimitInMillis,
                                                                   BranchMode branchMode) {
    auto **results = new ShortestPathResults * [set->getN()];
    for (int i = 0; i < set->getN(); i++) {
        results[i] = solve(set->getMatrices()[i], timeLimitInMillis, branchMode);
    }
    auto avg = PeaUtils::calculateAvgTime(set->getN(), results);
    return MultipleShortestPathResults::createFromShortestPathResults(set->getN(), results);
}

ShortestPathResults *BranchAndBoundMatrixReduction::solveLowCost(TspMatrix *matrix, long timeLimitInMillis) {
    auto start = std::chrono::high_resolution_clock::now();

    struct QueueComparator {
        bool operator()(const ReducedTspMatrix *a, ReducedTspMatrix *b) {
            return a->getCost() > b->getCost();
        }
    };

    long long upperBound = -1;
    ReducedTspMatrix *best = nullptr;

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
    ReducedTspMatrix *current;
    while (!queue.empty()) {
        current = queue.top();
        queue.pop();
        auto path = current->getPath();
        if (upperBound == -1 || current->getCost() < upperBound) {

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
                if (reduced->getPath().size() == matrix->getN()) {
                    if (upperBound == -1 || reduced->getCost() < upperBound) {
                        delete best;
                        best = reduced->copy();
                        upperBound = reduced->getCost();
                    }
                }
                auto currentTime = std::chrono::high_resolution_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start).count() >
                    timeLimitInMillis) {
                    return ShortestPathResults::createFailure();
                }

            }
        }
        delete current;
        auto currentTime = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start).count() >
            timeLimitInMillis) {
            return ShortestPathResults::createFailure();
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    int *path = new int[matrix->getN()];
    for (int i = 0; i < matrix->getN(); i++) {
        path[i] = best->getPath()[i];
    }
    return new ShortestPathResults(best->getCost(),
                                   best->getN(),
                                   path,
                                   std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
}

ShortestPathResults *BranchAndBoundMatrixReduction::solveDfs(TspMatrix *matrix, long timeLimitInMillis) {
    auto start = std::chrono::high_resolution_clock::now();

    long long upperBound = -1;
    ReducedTspMatrix *best = nullptr;

    std::vector<int> allVertices = PeaUtils::createVectorFromZeroToNMinusOne(matrix->getN());
    std::stack<ReducedTspMatrix *> stack;
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
    stack.push(rootPath);
    ReducedTspMatrix *current;
    while (!stack.empty()) {
        current = stack.top();
        stack.pop();
        auto path = current->getPath();
        if (upperBound == -1 || current->getCost() < upperBound) {
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
                stack.push(reduced);
                if (reduced->getPath().size() == matrix->getN()) {
                    if (upperBound == -1 || reduced->getCost() < upperBound) {
                        delete best;
                        best = reduced->copy();
                        upperBound = reduced->getCost();
                    }
                }
                auto currentTime = std::chrono::high_resolution_clock::now();
                if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start).count() >
                    timeLimitInMillis) {
                    return ShortestPathResults::createFailure();
                }

            }
        }
        delete current;
        auto currentTime = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start).count() >
            timeLimitInMillis) {
            return ShortestPathResults::createFailure();
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    int *path = new int[matrix->getN()];
    for (int i = 0; i < matrix->getN(); i++) {
        path[i] = best->getPath()[i];
    }
    return new ShortestPathResults(best->getCost(),
                                   best->getN(),
                                   path,
                                   std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

}

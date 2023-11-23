#include <iostream>
#include "DynamicProgramming.h"
#include "MultipleShortestPathResults.h"
#include <chrono>

ShortestPathResults *DynamicProgramming::solve(TspMatrix *matrix, long timeLimitInMillis) {
/**
 * Podejscie oparte o algorytm Helda-Karpa
 * Wzór na wyznaczenie kosztu sciezki:
 *      g(i, S) = min[k \in S] {C(i, k) + g(k, {S - {k})}
 *      gdzie:
 *          - g: koszt calkowitej sciezki
 *          - S: zbior wierzcholkow
 *          - i: wierzcholek startowy
 *          - C: funkcja oblicania kosztów
 *
 * Tablica memo to memoizacja przebytych drog
 * ma wymiary memo[ilosc wierzcholkow][rozmiar maski]
 * maska to prosta reprezentacja binarna pozostalych wierzcholkow do odwiedzenia 
 * np. rozmiar macierzy = 4, mamy do policzenia g(0, {1, 3}), to maska wynosi 0101
 * wartosc tej funkcji zapiszemy do memo[1][5]
 *
 *
 * **/
    auto start = std::chrono::high_resolution_clock::now();
    delete memo;
    delete memoPath;
    int n = matrix->getN();
    memo = new unsigned long long *[n];
    memoPath = new int *[n];
    for (int i = 0; i < n; i++) {
        memo[i] = new unsigned long long[1 << (n -1)];
        memoPath[i] = new int[1 << (n -1)];
        for (int j = 0; j < 1 << (n - 1); j++) {
            memo[i][j] = 0;
            memoPath[i][j] = 0;
        }
    }


    unsigned long long result = INT64_MAX;
    int bestChild = -1;

    for (int i = 1; i < n; i++) {
        int mask = ((1 << (n- 1)) - 1) & ~(1 << (i - 1));
        auto newResult = step(matrix, i, mask) + matrix->getMatrices()[0][i];
        if (newResult < result) {
            result = newResult;
            bestChild = i;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    int *path = new int[n];
    path[0] = 0;
    path[1] = bestChild;
    int S = (1 << (n- 1)) - 1;
    for (int i = 2; i < n; i++) {
        S &= ~(1 << (bestChild - 1));
        path[i] = memoPath[bestChild][S];
        bestChild = path[i];
    }
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return new ShortestPathResults(result, n, path, duration.count());
}

MultipleShortestPathResults *DynamicProgramming::solve(RandomTspMatrixSet *set, long timeLimitInMillis) {
    auto **results = new ShortestPathResults * [set->getN()];
    for (int i = 0; i < set->getN(); i++) {
        results[i] = solve(set->getMatrices()[i], timeLimitInMillis);
    }
    auto avg = PeaUtils::calculateAvgTime(set->getN(), results);
    return MultipleShortestPathResults::createFromShortestPathResults(set->getN(), results);

}

unsigned long long int DynamicProgramming::step(TspMatrix *matrix, int vertex, int mask) {
    if (mask == 0) {
        return matrix->getMatrices()[vertex][0];
    }
    if (memo[vertex][mask] != 0) {
        return memo[vertex][mask];
    }

    unsigned long long result = INT64_MAX;

    int bestChild = -1;
    for (int i = 1; i < matrix->getN(); i++) {
        if (i != vertex && (mask & (1 << (i - 1)))) {
            int newMask = mask & ~(1 << (i - 1));
            auto newResult = step(matrix, i, newMask) + matrix->getMatrices()[vertex][i];
            if (newResult < result) {
                result = newResult;
                bestChild = i;
            }
        }
    }

    memo[vertex][mask] = result;
    memoPath[vertex][mask] = bestChild;
    return result;

}

#include <iostream>
#include "DynamicProgramming.h"
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
    delete memo;
    int n = matrix->getN();
    memo = new unsigned long *[n];
    for (int i = 0; i < n; i++) {
        memo[i] = new unsigned long[1 << (n -1)];
        for (int j = 0; j < 1 << (n - 1); j++) {
            memo[i][j] = 0;
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    unsigned long long result = INT64_MAX;

    for (int i = 1; i < n; i++) {
        int mask = ((1 << (n- 1)) - 1) & ~(1 << (i - 1));
        result = std::min(result, step(matrix, i, mask) + matrix->getMatrices()[0][i]); // maska wszystkie jedynki
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << result << std::endl;
    std::cout << duration.count();
    return nullptr;
}

unsigned long long int DynamicProgramming::step(TspMatrix *matrix, int vertex, int mask) {
    if (mask == 0) {
        return matrix->getMatrices()[vertex][0];
    }
    if (memo[vertex][mask] != 0) {
        return memo[vertex][mask];
    }

    unsigned long long result = INT64_MAX;

    for (int i = 1; i < matrix->getN(); i++) {
        if (i != vertex && (mask & (1 << (i - 1)))) {
            int newMask = mask & ~(1 << (i - 1));
            result = std::min(result, step(matrix, i, newMask) + matrix->getMatrices()[vertex][i]);
        }
    }

    memo[vertex][mask] = result;
    return result;

}

#include <iostream>
#include <cstring>
#include <fstream>
#include "PeaUtils.h"
#include "BruteForce.h"
#include "RandomTspMatrixSet.h"
#include "BranchAndBoundMatrixReduction.h"
#include "DynamicProgramming.h"

using std::cout;
using std::endl;
using std::cin;

void menu();

void readFromFileAndTest();

void randomTest();

void fullTests();

void performanceTest(int instanceCount, int graphSize, bool withBruteForce);

void ensurePathGood(TspMatrix *matrix, int *path, unsigned long long cost);

int main(int argc, char *argv[]) {
//    auto matrix = PeaUtils::generateRandomTSPInstance(11);
//    cout << BruteForce::performShortestPath(matrix, 500000)->toString() << endl;
//    cout << BranchAndBoundMatrixReduction::solve(matrix, 100000, LOW_COST)->toString() << endl;
//    cout << BranchAndBoundMatrixReduction::solve(matrix, 100000, DFS)->toString() << endl;
//    cout << DynamicProgramming::solve(matrix, 100000)->toString() << endl;
//    performanceTest(10, 25);
    menu();
}

void menu() {
    bool program = true;
    int option;
    while (program) {
        cout << "Wybierz opcje: " << endl;
        cout << "1) Rozwiaz graf z pliku" << endl;
        cout << "2) Przeprowadz testy na losowych instancjach" << endl;
        cout << "3) Wyjdz" << endl;
        cin >> option;
        getchar();
        if (option == 1) {
            readFromFileAndTest();
        } else if (option == 2) {
            randomTest();
        } else if (option == 3) {
            program = false;
        } else {
            cout << "Nie ma takiej opcji" << endl;
        };

    }
}

void readFromFileAndTest() {
    cout << "Podaj nazwe pliku: ";
    cout << "Podaj nazwe pliku: ";
    std::string fileName;
    std::getline(std::cin, fileName);
    auto matrix = PeaUtils::readMatrixFromFile(fileName);
    int option;
    int program = true;
    while (program) {
        cout << "Wybierz metode (limit 500 s)" << endl;
        cout << "1) Brute force" << endl;
        cout << "2) Branch and bound (low cost)" << endl;
        cout << "3) Branch and bound (DFS)" << endl;
        cout << "4) Programowanie dynamiczne" << endl;
        cout << "5) Zakoncz testy" << endl;
        cin >> option;
        getchar();
        if (option == 1) {
            cout << BruteForce::performShortestPath(matrix, 500000)->toString() << endl;
        } else if (option == 2) {
            cout << BranchAndBoundMatrixReduction::solve(matrix, 500000, LOW_COST)->toString() << endl;
        } else if (option == 3) {
            cout << BranchAndBoundMatrixReduction::solve(matrix, 500000, DFS)->toString() << endl;
        } else if (option == 4) {
            cout << DynamicProgramming::solve(matrix, 500000)->toString() << endl;
        } else if (option == 5) {
            program = false;
        } else {
            cout << "Nie ma takiej opcji" << endl;
        }
    }
    delete matrix;

}

void randomTest() {
    int instanceCount;
    int graphSize;
    int includeBruteforce;
    cout << "Podaj wielkosc macierzy: ";
    cin >> graphSize;
    getchar();
    cout << "Podaj ilosc macierzy: ";
    cin >> instanceCount;
    getchar();
    cout << "Uwzglednic brute force (1 - tak, 2 - nie): ";
    cin >> includeBruteforce;
    getchar();
    if (includeBruteforce == 1) {
        performanceTest(instanceCount, graphSize, true);
    } else {
        performanceTest(instanceCount, graphSize, false);
    }
}

void performanceTest(int instanceCount, int graphSize, bool withBruteForce) {
    cout << "GRAPH SIZE: " << graphSize << endl;
    cout << "INSTANCE SIZE: " << instanceCount << endl;
    auto set = new RandomTspMatrixSet(instanceCount, graphSize);
    if (withBruteForce) {
        cout << "BRUTE FORCE" << endl;
        cout << BruteForce::performShortestPath(set, 500000)->toString() << endl;
    }
    cout << "BXB (LOW COST)" << endl;
    cout << BranchAndBoundMatrixReduction::solve(set, 300000, LOW_COST)->toString() << endl;
    cout << "BXB (DFS)" << endl;
    cout << BranchAndBoundMatrixReduction::solve(set, 300000, DFS)->toString() << endl;
    cout << "HELD-KARP" << endl;
    cout << DynamicProgramming::solve(set, 300000)->toString() << endl;
    delete set;
}

void fullTests() {
    std::vector<std::string> filenames = {
            "../Graphs/tsp_6_1.txt",
            "../Graphs/tsp_6_2.txt",
            "../Graphs/tsp_10.txt",
            "../Graphs/tsp_12.txt",
            "../Graphs/tsp_13.txt",
            "../Graphs/tsp_14.txt",
            "../Graphs/tsp_15.txt",
            "../Graphs/tsp_17_1.txt",
//            "../Graphs/tsp_17_bxb_killer.txt",
            "../Graphs/tsp_18_1.txt",
            "../Graphs/tsp_19_1.txt",
            "../Graphs/tsp_20_1.txt"
    };

    for (const auto &fileName: filenames) {
        cout << "PLIK: " << fileName << endl;
        auto matrix = PeaUtils::readMatrixFromFile(fileName);

//        cout << "BruteForce" << endl;
//        ShortestPathResults *bfResult = BruteForce::performShortestPath(matrix, 500000);
//        cout << bfResult->toString() << endl;
//        ensurePathGood(matrix, bfResult->getPath(), bfResult->getCost());

        cout << "BxB (low-cost)" << endl;
        ShortestPathResults *bxbLcResult = BranchAndBoundMatrixReduction::solve(matrix, 300000, LOW_COST);
        cout << bxbLcResult->toString() << endl;
        ensurePathGood(matrix, bxbLcResult->getPath(), bxbLcResult->getCost());

        cout << "BxB (DFS)" << endl;
        ShortestPathResults *bxbDfsResult = BranchAndBoundMatrixReduction::solve(matrix, 300000, DFS);
        cout << bxbDfsResult->toString() << endl;
        ensurePathGood(matrix, bxbDfsResult->getPath(), bxbDfsResult->getCost());

        cout << "Dynamicznie" << endl;
        ShortestPathResults *dynamicResult = DynamicProgramming::solve(matrix, 300000);
        cout << dynamicResult->toString() << endl << endl << endl;
        ensurePathGood(matrix, dynamicResult->getPath(), dynamicResult->getCost());
        _sleep(1000);
        delete matrix;
    }
}

void ensurePathGood(TspMatrix *matrix, int *path, unsigned long long int cost) {
    if (matrix->calculateCost(path) != cost) {
        throw std::invalid_argument("BAD COST");
    }
}



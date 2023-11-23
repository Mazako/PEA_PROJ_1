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

void menu();

void fullTests();

int main(int argc, char *argv[]) {
//    auto matrix = PeaUtils::generateRandomTSPInstance(5);
//    cout << BranchAndBoundMatrixReduction::solve(matrix, 100000, LOW_COST)->toString() << endl;
//    cout << BranchAndBoundMatrixReduction::solve(matrix, 100000, DFS)->toString() << endl;
//    cout << DynamicProgramming::solve(matrix, 100000)->toString() << endl;
    fullTests();
}

void menu() {
    bool program = true;
    while (program) {
        cout << "Wybierz opcje" << endl;
        cout << "1) Przeglad zupelny" << endl;
        cout << "2) Branch and bound" << endl;
        cout << "3) Programowanie dynamiczne (algorytm Helda-Karpa)" << endl;
        cout << "4) Pelne testy" << endl;
        cout << "5) Zakoncz program" << endl;
        std::string choice;
        std::getline(std::cin, choice);
        if (choice != "1" && choice != "2" && choice != "3" && choice != "4") {
            cout << "Nie ma takiej opcji" << endl;
        } else if (choice == "5") {
            program = false;
        } else if (choice == "4") {
            fullTests();
        } else {
            cout << "Podaj nazwe pliku: ";
            std::string fileName;
            std::getline(std::cin, fileName);
            auto matrix = PeaUtils::readMatrixFromFile(fileName);
            if (choice == "1") {
                cout << BruteForce::performShortestPath(matrix, 10000000)->toString() << endl;
            } else if (choice == "2") {
//                cout << BranchAndBoundMatrixReduction::solve(matrix, 10000000, nullptr)->toString() << endl;
            } else {
                cout << DynamicProgramming::solve(matrix, 100000000)->toString() << endl;
            }
        }
    }
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
            "../Graphs/tsp_17_bxb_killer.txt",
            "../Graphs/tsp_18_1.txt",
            "../Graphs/tsp_19_1.txt",
            "../Graphs/tsp_20_1.txt"
    };

    for (int i = 0; i < filenames.size(); i++) {
        auto fileName = filenames[i];
        cout << "PLIK: " << fileName << endl;
        if (i < 7) {
            auto matrix = PeaUtils::readMatrixFromFile(fileName);
            cout << "BruteForce" << endl;
            cout << BruteForce::performShortestPath(matrix, 300000)->toString() << endl;
            delete matrix;
        }
        auto matrix = PeaUtils::readMatrixFromFile(fileName);
        cout << "BxB (low-cost)" << endl;
        cout << BranchAndBoundMatrixReduction::solve(matrix, 300000, LOW_COST)->toString() << endl;
        delete matrix;
        matrix = PeaUtils::readMatrixFromFile(fileName);
        cout << "BxB (DFS)" << endl;
        cout << BranchAndBoundMatrixReduction::solve(matrix, 300000, DFS)->toString() << endl;
        delete matrix;
        matrix = PeaUtils::readMatrixFromFile(fileName);
        cout << "Dynamicznie" << endl;
        cout << DynamicProgramming::solve(matrix, 300000)->toString() << endl;
        delete matrix;
    }
}



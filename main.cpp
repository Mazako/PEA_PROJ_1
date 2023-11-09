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
const char *BRUTE_FORCE_ARG = "GENERATE_BRUTE";

void generateBruteForceData(int matrixSize, int count);

void menu();

void fullTests();

int main(int argc, char *argv[]) {
    if (argc != 1) {
        auto argument = argv[1];
        int matrixSize = atoi(argv[2]);
        int count = atoi(argv[3]);
        if (strcmp(argument, BRUTE_FORCE_ARG) == 0) {
            cout << "Starting program in brute_force data generation mode." << endl;
            generateBruteForceData(matrixSize, count);
        }
    } else {
        menu();
    }

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
                cout << BranchAndBoundMatrixReduction::solve(matrix, 10000000)->toString() << endl;
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
            "../Graphs/tsp_18_1.txt",
            "../Graphs/tsp_19_1.txt",
            "../Graphs/tsp_20_1.txt"
    };

    for (const auto &fileName: filenames) {
        cout << fileName << endl;
        auto matrix = PeaUtils::readMatrixFromFile(fileName);
        cout << "BxB" << endl;
        cout << BranchAndBoundMatrixReduction::solve(matrix, 1000000000)->toString() << endl;
        cout << "Dynamicznie" << endl;
        cout << DynamicProgramming::solve(matrix, 1000000000)->toString() << endl;
        delete matrix;
    }
}


void generateBruteForceData(int matrixSize, int count) {
    std::ofstream file;
    file.open("brute_force_sample.txt");
    file << matrixSize << " " << count << endl << endl;
    auto set = new RandomTspMatrixSet(count, matrixSize);
    for (int i = 0; i < count; i++) {
        auto currMatrix = set->getMatrices()[i];
        file << PeaUtils::matrixToString(currMatrix) << endl;
        auto result = BruteForce::performShortestPath(currMatrix, 1000000);
        file << result->getCost() << ";" << PeaUtils::arrayToString(result->getN(), result->getPath()) << endl;
        if (i != count - 1) {
            file << endl;
        }
        delete result;
    }
    delete set;
    file.close();
}

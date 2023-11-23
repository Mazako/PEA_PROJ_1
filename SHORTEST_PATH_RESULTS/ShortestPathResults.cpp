#include "ShortestPathResults.h"

ShortestPathResults::ShortestPathResults(unsigned long long int cost, int n, int *path, long long nanoTime) : cost(cost), path(path), n(n), nanoTime(nanoTime), success(true) {}

ShortestPathResults::~ShortestPathResults() {
    delete this->path;
}

std::string ShortestPathResults::toString() {
    if (!success) {
        std::string str;
        str.append("Ilosc wierzcholkow: ").append(std::to_string(n));
        str.append("\t PORAZKA");
        return str;
    }
    std::string str;
    str.append("Ilosc wierzcholkow: ").append(std::to_string(n));
    str.append("\tkoszt: ").append(std::to_string(cost));
    str.append("\tsciezka: ");
    for (int i = 0; i < n; i++) {
        str.append(std::to_string(path[i])).append(" ");
    }
    str.append("\tczas: ").append(std::to_string((double) nanoTime / 1000000)).append(" ms.");
    return str;
}

ShortestPathResults *ShortestPathResults::createFailure() {
    return new ShortestPathResults(false);
}

ShortestPathResults::ShortestPathResults(bool success) {
    this->nanoTime = 0;
    this->n = 0;
    this->cost = 0;
    this->success = false;
    this->path = nullptr;
}

bool ShortestPathResults::isSuccess() const {
    return success;
}

unsigned long long int ShortestPathResults::getCost() const {
    return cost;
}

int *ShortestPathResults::getPath() const {
    return path;
}

int ShortestPathResults::getN() const {
    return n;
}

long long int ShortestPathResults::getNanoTime() const {
    return nanoTime;
}

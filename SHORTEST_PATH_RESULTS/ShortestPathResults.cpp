#include "ShortestPathResults.h"

ShortestPathResults::ShortestPathResults(unsigned long long int cost, int n, int *path, long nanoTime) : cost(cost), path(path), n(n), nanoTime(nanoTime), success(true) {}

ShortestPathResults::~ShortestPathResults() {
    delete this->path;
}

std::string ShortestPathResults::toString() {
    std::string str;
    str.append("koszt: ").append(std::to_string(cost));
    str.append("\tsciezka: ");
    for (int i = 0; i < n; i++) {
        str.append(std::to_string(path[i])).append(" ");
    }
    return str;
}

ShortestPathResults *ShortestPathResults::createFailure() {
    return new ShortestPathResults(false);
}

ShortestPathResults::ShortestPathResults(bool success) {
    this->success = false;
}

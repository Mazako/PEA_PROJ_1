#include "MultipleShortestPathResults.h"

MultipleShortestPathResults::MultipleShortestPathResults(long double n, long double avgTime) : n(n), avgTime(avgTime) {}

long double MultipleShortestPathResults::getN() const {
    return n;
}

long double MultipleShortestPathResults::getAvgTime() const {
    return avgTime;
}

std::string MultipleShortestPathResults::toString() {
    std::string x;
    x.append("Ilosc wierzcholkow: ")
        .append(std::to_string(n))
        .append("\tSredni czas: ")
        .append(std::to_string(avgTime));
    return x;
}

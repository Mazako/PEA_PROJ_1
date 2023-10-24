#include "MultipleShortestPathResults.h"

MultipleShortestPathResults::MultipleShortestPathResults(long n, long double avgTime) : n(n), avgTime(avgTime) {}

long  MultipleShortestPathResults::getN() const {
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

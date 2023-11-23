#include "MultipleShortestPathResults.h"
#include "PeaUtils.h"

MultipleShortestPathResults::MultipleShortestPathResults(long n, long double avgTime, long double std,
                                                         double successRate) : n(n), avgTime(avgTime), std(std),
                                                                               successRate(successRate) {}

std::string MultipleShortestPathResults::toString() {
    std::string x;
    x.append("Ilosc wierzcholkow: ")
        .append(std::to_string(n))
        .append("\tSredni czas: ")
        .append(std::to_string(avgTime / 1000000))
        .append("\tOdchylenie standardowe: ")
        .append(std::to_string(std / 1000000))
        .append("\tSukcesow: ")
        .append(std::to_string(successRate));
    return x;
}

MultipleShortestPathResults *MultipleShortestPathResults::createFromShortestPathResults(int n, ShortestPathResults **results) {
    long double avg = PeaUtils::calculateAvgTime(n, results);
    long double std = PeaUtils::calculateStandardDeviation(n, results, avg);
    double successRate = PeaUtils::calculateSuccessRate(n, results);
    return new MultipleShortestPathResults(n, avg, std, successRate);
}

long double MultipleShortestPathResults::getStd() const {
    return std;
}

long double MultipleShortestPathResults::getAvgTime() const {
    return avgTime;
}

long  MultipleShortestPathResults::getN() const {
    return n;
}

double MultipleShortestPathResults::getSuccessRate() const {
    return successRate;
}

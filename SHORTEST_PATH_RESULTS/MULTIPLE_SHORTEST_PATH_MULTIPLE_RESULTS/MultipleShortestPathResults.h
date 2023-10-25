#ifndef PEA_PROJ_1_MULTIPLESHORTESTPATHRESULTS_H
#define PEA_PROJ_1_MULTIPLESHORTESTPATHRESULTS_H

#include <string>
#include "ShortestPathResults.h"
class MultipleShortestPathResults {
private:
    long n;
    long double avgTime;
    long double std;
    double successRate;
public:
    MultipleShortestPathResults(long n, long double avgTime, long double std, double successRate);

    long getN() const;

    long double getAvgTime() const;

    long double getStd() const;

    double getSuccessRate() const;

    std::string toString();

    static MultipleShortestPathResults* createFromShortestPathResults(int n, ShortestPathResults **results);
};


#endif //PEA_PROJ_1_MULTIPLESHORTESTPATHRESULTS_H

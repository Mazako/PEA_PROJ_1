#ifndef PEA_PROJ_1_MULTIPLESHORTESTPATHRESULTS_H
#define PEA_PROJ_1_MULTIPLESHORTESTPATHRESULTS_H

#include <string>
class MultipleShortestPathResults {
private:
    long double n;
    long double avgTime;

public:
    MultipleShortestPathResults(long double n, long double avgTime);

    long double getN() const;

    long double getAvgTime() const;

    std::string toString();
};


#endif //PEA_PROJ_1_MULTIPLESHORTESTPATHRESULTS_H

#ifndef PEA_PROJ_1_SHORTESTPATHRESULTS_H
#define PEA_PROJ_1_SHORTESTPATHRESULTS_H
#include <string>

class ShortestPathResults {
private:
    bool success;
    int cost;
    int* path;
    int n;
    long nanoTime;
    ShortestPathResults(bool success);
public:
    ShortestPathResults(int cost, int n, int *path, long nanoTime);
    static ShortestPathResults* createFailure();
    ~ShortestPathResults();
    std::string toString();
};


#endif //PEA_PROJ_1_SHORTESTPATHRESULTS_H

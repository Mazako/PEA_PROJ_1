#ifndef PEA_PROJ_1_SHORTESTPATHRESULTS_H
#define PEA_PROJ_1_SHORTESTPATHRESULTS_H
#include <string>

class ShortestPathResults {
private:
    bool success;
    unsigned long long int cost;
    int* path;
    int n;
    long long nanoTime;
    ShortestPathResults(bool success);
public:
    ShortestPathResults(unsigned long long int cost, int n, int *path, long long nanoTime);
    static ShortestPathResults* createFailure();
    ~ShortestPathResults();
    std::string toString();

    bool isSuccess() const;

    unsigned long long int getCost() const;

    int *getPath() const;

    int getN() const;

    long long int getNanoTime() const;
};


#endif //PEA_PROJ_1_SHORTESTPATHRESULTS_H

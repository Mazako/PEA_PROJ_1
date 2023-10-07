#include <iostream>
#include "PEA_UTILS/PeaUtils.h"

using std::cout;
using std::endl;

int main() {
    TspMatrix* matrix = PeaUtils::generateRandomTSPInstance();
    std::string res = PeaUtils::matrixToString(matrix);
    cout << res << endl;
    delete matrix;
}

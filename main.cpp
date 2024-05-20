#include <iostream>
#include "GeneralFunctions.h"

using namespace std;

int main() {
    int k = 0; // number of graphs
    int n; // order of graph
    char tmp;
    cin >> k;
    for (int i = 0; i < k; i++) {
        n = getGraphOrder(tmp);
        degreeSequence(n);
    }
    return 0;
}
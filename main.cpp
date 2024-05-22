#include <iostream>
#include "GeneralFunctions.h"

using namespace std;

int main() {
    int k = 0; // number of graphs
    long long int order; // order of graph
    char tmp;
    cin >> k;
    for (int i = 0; i < k; i++) {
        order = getGraphOrder(tmp);
        degreeSequence(order);
        printf("\n");
    }
    return 0;
}

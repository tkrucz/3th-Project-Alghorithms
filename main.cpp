#include "GeneralFunctions.h"

int main() {
    int k; // number of graphs
    long long int order; // order of graph
    char tmp;
    k = getNumber(tmp);
    for (int i = 0; i < k; i++) {
        order = getGraphOrder(tmp);
        degreeSequence(order);
        printf("\n");
    }
    return 0;
}
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
        printf("\n?"); // number of components;
        printf("\n?"); // bipartiteness;
        printf("\n?"); // the eccentricity of vertices
        printf("\n?"); // planarity
        printf("\n?"); // vertices colours GREEDY
        printf("\n?"); // vertices colours LFS
        printf("\n?"); // vertices colours SLF
        printf("\n?"); // the number of different C4 subgraphs
        printf("\n?"); // the number of the graph complement's edges
        printf("\n");
    }
    return 0;
}
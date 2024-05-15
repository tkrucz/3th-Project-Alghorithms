#include <iostream>
#include "GeneralFunctions.h"

using namespace std;

int main() {
    int k = 0; // number of graphs
    int n = 0; // order of graph
    char tmp;
    // cout << "Hello world" << endl;
    cin >> k;
    for (int i = 0; i < k; i++) {
        // input whole graph
        degreeSequence(tmp,n);
    }
    return 0;
}

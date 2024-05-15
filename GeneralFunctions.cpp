#include "GeneralFunctions.h"

int getGraphOrder(char &tmp, int &n) {
    n = 0;
    tmp = getchar();
    if (tmp == '\n' || tmp == ' ')
        tmp = getchar();
    while (tmp >= '0' && tmp <= '9') {
        int digit = tmp - '0';
        n = n * 10 + digit;
        tmp = getchar();
    }
    return n;
}

void degreeSequence(char &tmp, int& n) {
    int deg;
    n = getGraphOrder(tmp, n);
    int degreeSequence[n];
    for (int i = 0; i < n; i++) {
        cin >> deg;
        degreeSequence[i] = deg;
        cout << degreeSequence[i] << endl;
        for(int j=0; j<deg; j++){
            getchar(); // Space
            getchar(); // Vertex IDs
        }
        getchar(); // End of line
    }
}
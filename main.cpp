#include "GeneralFunctions.h"

int main() {
    int k; // number of graphs
    char tmp;
    k = getNumber(tmp);
    for (int i = 0; i < k; i++) {
        printAnswer(tmp);
    }
    return 0;
}
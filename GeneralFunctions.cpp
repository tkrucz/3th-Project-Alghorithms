#include "GeneralFunctions.h"

bool compare(int num1, int num2) {
    return num1 > num2;
}

void merge(int *arr, int firstIndex, int middleIndex, int lastIndex) {
    int size = lastIndex - firstIndex + 1;
    int *tmp = new int[size];

    int i = firstIndex;
    int j = middleIndex + 1;
    int k = 0;

    while (i <= middleIndex && j <= lastIndex) {
        if (compare(arr[i], arr[j])) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
        }
    }

    while (i <= middleIndex) {
        tmp[k++] = arr[i++];
    }

    while (j <= lastIndex) {
        tmp[k++] = arr[j++];
    }

    for (int i = 0; i < size; i++) {
        arr[firstIndex++] = tmp[i];
    }

    delete[] tmp;
}

void mergeSort(int *arr, int firstIndex, int lastIndex) {
    if (firstIndex >= lastIndex)
        return;

    int middleIndex = (firstIndex + lastIndex) / 2;
    mergeSort(arr, firstIndex, middleIndex);
    mergeSort(arr, middleIndex + 1, lastIndex);

    merge(arr, firstIndex, middleIndex, lastIndex);
}

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
        for(int j=0; j<deg; j++){
            getchar(); // Space
            getchar(); // Vertex IDs
        }
        getchar(); // End of line
    }

    mergeSort(degreeSequence,0,n-1);

    for (int i = 0; i < n; ++i) {
        cout << degreeSequence[i] << ' ';
    }
}
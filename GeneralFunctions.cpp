#include "GeneralFunctions.h"

struct Stack {
    int *elements;
    int top;
    int capacity;

    Stack(int size) : top(-1), capacity(size) {
        elements = new int[size];
    }

    ~Stack() {
        delete[] elements;
    }

    void push(int x) {
        if (top < capacity - 1) {
            elements[++top] = x;
        }
    }

    int pop() {
        if (top >= 0) {
            return elements[top--];
        }
        return -1; // Error value
    }

    bool isEmpty() {
        return top == -1;
    }
};

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

int getGraphOrder(char &tmp) {
    int n=0;
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

void degreeSequence(int order) {
    int deg;
    int ver;
    int degreeSequence[order];
    Vector *adjMat = adjMatAlloc(order);
    for (int i = 0; i < order; i++) {
        cin >> deg;
        degreeSequence[i] = deg;
        for (int j = 0; j < deg; j++) {
            cin >> ver;
            adjMat[i].push_back(ver);
        }
        getchar(); // End of line
    }

    mergeSort(degreeSequence, 0, order - 1);

    for (int i = 0; i < order; ++i) {
        cout << degreeSequence[i] << ' ';
    }
    cout << endl;

    cout << "Adjacency Matrix " << endl;
    for (int i = 0; i < order; ++i) {
        for (int j = 0; j < adjMat[i].Size(); ++j) {
            int value = adjMat[i].get(j);
            cout << value << ',';
        }
        cout << endl;
    }

    freeSpace(adjMat);
}

bool dfs(int **adjMat, int order, int start) {

    bool *visited = new bool[order];
    for (int i = 0; i < order; ++i) {
        visited[i] = false;
    }

    Stack path(order);
    path.push(start);

    while (!path.isEmpty()) {
        int current = path.pop();

        if (!visited[current]) {
            visited[current] = true;
            cout << "Visited vertex: " << current + 1 << endl;
        }

        for (int i = 0; i < order; ++i) {
            if (adjMat[current][i] == 1 && !visited[i]) {
                path.push(i);
            }
        }
    }

    // Check if all vertices are visited (or any other condition as needed)
    bool allVisited = true;
    for (int i = 0; i < order; ++i) {
        if (!visited[i]) {
            allVisited = false;
            break;
        }
    }
    delete[] visited;
    return allVisited;
}

Vector* adjMatAlloc(int order){
    Vector *adjMat=new Vector[order];
    return adjMat;
}

void freeSpace(Vector *adjMat){
    delete[] adjMat;
}
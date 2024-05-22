#include "GeneralFunctions.h"

struct Stack {
    int *elements;
    int top;
    long long int capacity;

    Stack(long long int size) : top(-1), capacity(size) {
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

    bool contains(int x) {
        for (int i = 0; i <= top; ++i) {
            if (elements[i] == x) {
                return true;
            }
        }
        return false;
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

    for (int u = 0; u < size; u++) {
        arr[firstIndex++] = tmp[u];
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
    int n = 0;
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

void degreeSequence(long long int order) {
    int deg = 0;
    int ver = 0;
    long long int complementsEdges = 0;
    int *degreeSequence = new int[order];
    for (int i = 0; i < order; ++i) {
        degreeSequence[i] = 0;
    }
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

//    cout << "Adjacency Matrix " << endl;
//    for (int i = 0; i < order; ++i) {
//        for (int j = 0; j < adjMat[i].Size(); ++j) {
//            int value = adjMat[i].get(j);
//            cout << value << ',';
//        }
//        cout << endl;
//    }

    printf("\n"); // endl after degree sequence
    cout << countComponents(adjMat, order, complementsEdges);

    if (bipartite(adjMat, order))
        printf("\nT");
    else
        printf("\nF");

    printNotImplemented();
    printf("\n%lld", complementsEdges);

    delete[] degreeSequence;
    freeSpace(adjMat);
}

int countComponents(Vector *adjMat, long long int order, long long int &complementsEdges) {
    bool *visited = new bool[order];
    for (int i = 0; i < order; ++i) {
        visited[i] = false;
    }

    int components = 0;
    long long int edges = 0;

    for (int i = 0; i < order; ++i) {
        if (!visited[i]) {
            components++;
            dfs(adjMat, order, i + 1, visited, edges);
        }
    }

    complementsEdges = order * (order - 1) / 2;
    edges = edges / 2;
    complementsEdges = complementsEdges - edges;

    delete[] visited;
    return components;
}

void dfs(Vector *adjMat, long long int order, int start, bool *visited, long long int &edges) {
    Stack path(order);
    path.push(start);

    while (!path.isEmpty()) {
        int current = path.pop();

        if (current != 0)
            current--;

        if (!visited[current]) {
            visited[current] = true;

            // Explore neighbors of the current vertex
            Vector &neighbors = adjMat[current];
            for (int i = 0; i < neighbors.Size(); ++i) {
                int neighbor = neighbors.get(i);
                edges++;
                if (!visited[neighbor - 1] && !path.contains(neighbor)) {
                    path.push(neighbor);
                }
            }
        }
    }
}

bool bipartite(Vector *adjMat, long long int order) {
    bool *visited = new bool[order];
    for (int i = 0; i < order; ++i) {
        visited[i] = false;
    }

    int *bipartite = new int[order];
    for (int i = 0; i < order; ++i) {
        bipartite[i] = 0;
    }
    bipartite[0] = 1;

    for (int i = 0; i < order; ++i) {
        if (!visited[i]) {
            bipartiteDFS(adjMat, order, i + 1, visited, bipartite);
        }
    }

    for (int i = 0; i < order; i++) {
        int group = bipartite[i];
        for (int j = 0; j < adjMat[i].Size(); j++) {
            int neighbour = adjMat[i].get(j);
            if (bipartite[neighbour - 1] == group) {
                return false;
            }
        }
    }
    delete[] visited;
    delete[] bipartite;
    return true;
}

void bipartiteDFS(Vector *adjMat, long long int order, int start, bool *visited, int *bipartite) {
    Stack path(order);
    path.push(start);
    int group = 0;

    while (!path.isEmpty()) {
        int current = path.pop();

        if (current != 0)
            current--;

        if (!visited[current]) {
            visited[current] = true;
            if (bipartite[current] == 1)
                group = 2;
            else
                group = 1;


            // Explore neighbors of the current vertex
            Vector &neighbors = adjMat[current];
            for (int i = 0; i < neighbors.Size(); ++i) {
                int neighbor = neighbors.get(i);
                if (!visited[neighbor - 1] && !path.contains(neighbor)) {
                    path.push(neighbor);
                    bipartite[neighbor - 1] = group;
                }
            }
        }
    }
}

Vector *adjMatAlloc(long long int order) {
    Vector *adjMat = new Vector[order];
    return adjMat;
}

void freeSpace(Vector *adjMat) {
    delete[] adjMat;
}

void printNotImplemented() {
    printf("\n?"); // the eccentricity of vertices
    printf("\n?"); // planarity
    printf("\n?"); // vertices colours GREEDY
    printf("\n?"); // vertices colours LFS
    printf("\n?"); // vertices colours SLF
    printf("\n?"); // the number of different C4 subgraphs
}
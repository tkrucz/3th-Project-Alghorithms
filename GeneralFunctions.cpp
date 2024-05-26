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
};

void merge(Vertex_ID_AND_DEGREE *arr, int firstIndex, int middleIndex, int lastIndex) {
    int size = lastIndex - firstIndex + 1;
    Vertex_ID_AND_DEGREE *tmp = new Vertex_ID_AND_DEGREE[size];

    int i = firstIndex;
    int j = middleIndex + 1;
    int k = 0;

    while (i <= middleIndex && j <= lastIndex) {
        if (arr[i].degree > arr[j].degree || (arr[i].degree == arr[j].degree && arr[i].id < arr[j].id)) {
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
        arr[firstIndex + u] = tmp[u];
    }

    delete[] tmp;
}

void mergeSort(Vertex_ID_AND_DEGREE *arr, int firstIndex, int lastIndex) {
    if (firstIndex >= lastIndex)
        return;

    int middleIndex = (firstIndex + lastIndex) / 2;
    mergeSort(arr, firstIndex, middleIndex);
    mergeSort(arr, middleIndex + 1, lastIndex);

    merge(arr, firstIndex, middleIndex, lastIndex);
}

int getGraphOrder(char &tmp) {
    return getNumber(tmp);
}

void degreeSequence(long long int order) {
    int deg, ver;
    long long int complementsEdges = 0;
    Vertex_ID_AND_DEGREE *table = new Vertex_ID_AND_DEGREE[order];
    char tmp;

    for (int i = 0; i < order; ++i) {
        table[i] = {i, 0};
    }

    Vector *adjMat = adjMatAlloc(order);

    for (int i = 0; i < order; i++) {
        deg = getNumber(tmp);
        table[i].degree = deg;
        for (int j = 0; j < deg; j++) {
            ver = getNumber(tmp);
            adjMat[i].push_back(ver);
        }
        if (tmp != '\n')
            getchar(); // End of line
    }

    mergeSort(table, 0, order - 1);
    int maxDegree = table[0].degree;

    for (int i = 0; i < order; ++i) {
        printf("%d ", table[i].degree);
    }

    printf("\n%d", countComponents(adjMat, order, complementsEdges));


    if (bipartite(adjMat, order))
        printf("\nT");
    else
        printf("\nF");

    printf("\n?"); // the eccentricity of vertices
    printf("\n?"); // planarity
    printf("\n"); // endl after planarity

    coloursGreedy(adjMat, order, maxDegree);
    printf("\n"); // endl after colours greedy
    coloursLF(adjMat, table, order, maxDegree);

    printNotImplemented();

    printf("\n%lld", complementsEdges);

    delete[] table;
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

    complementsEdges = order * (order - 1) / 2; // formula for complements edges
    edges = edges / 2; // dfs counts the same edges twice
    complementsEdges = complementsEdges - edges;

    delete[] visited;
    return components;
}

void dfs(Vector *adjMat, long long int order, int start, bool *visited, long long int &edges) {
    Stack path(order);
    path.push(start);

    visited[start - 1] = true;

    while (!path.isEmpty()) {
        int current = path.pop();

        if (current != 0)
            current--;

        // Explore neighbors of the current vertex
        Vector &neighbors = adjMat[current];
        for (int i = 0; i < neighbors.Size(); ++i) {
            int neighbor = neighbors.get(i);
            edges++;
            if (!visited[neighbor - 1]) {
                path.push(neighbor);
                visited[neighbor - 1] = true;
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

    // Check if current vertex is connected with vertex which has the same group
    for (int i = 0; i < order; i++) {
        int group = bipartite[i];
        for (int j = 0; j < adjMat[i].Size(); j++) {
            int neighbour = adjMat[i].get(j);
            if (bipartite[neighbour - 1] == group) {
                delete[] visited;
                delete[] bipartite;
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

    int group;
    visited[start - 1] = true;

    while (!path.isEmpty()) {
        int current = path.pop();

        if (current != 0)
            current--;

        if (bipartite[current] == 1)
            group = 2;
        else
            group = 1;

        // Explore neighbors of the current vertex
        Vector &neighbors = adjMat[current];
        for (int i = 0; i < neighbors.Size(); ++i) {
            int neighbor = neighbors.get(i);
            if (!visited[neighbor - 1]) {
                path.push(neighbor);
                visited[neighbor - 1] = true;
                bipartite[neighbor - 1] = group;
            }
        }
    }
}

void coloursGreedy(Vector *adjMat, long long int order, int maxDegree) {
    bool *visited = new bool[maxDegree + 1];

    int *coloursGreedy = new int[order];
    for (int i = 0; i < order; ++i) {
        coloursGreedy[i] = -1; // No colour at the beginning
    }
    coloursGreedy[0] = 1;


    for (int u = 0; u < order; ++u) {

        for (int i = 0; i < maxDegree + 1; ++i) {
            visited[i] = false;
        }

        // Mark colors used by adjacent vertices as unavailable
        for (int i = 0; i < adjMat[u].Size(); ++i) {
            int neighbour = adjMat[u].get(i) - 1;
            if (coloursGreedy[neighbour] != -1) {
                visited[coloursGreedy[neighbour] - 1] = true;
            }
        }

        // Find the first available colour
        int color;
        for (color = 0; color < maxDegree + 1; ++color) {
            if (!visited[color]) {
                break;
            }
        }

        coloursGreedy[u] = color + 1;
    }

    for (int i = 0; i < order; i++)
        printf("%d ", coloursGreedy[i]);

    delete[] visited;
    delete[] coloursGreedy;
}

void coloursLF(Vector *adjMat, Vertex_ID_AND_DEGREE *arr, long long int order, int maxDegree) {

    bool *visited = new bool[maxDegree + 1];

    int *coloursLF = new int[order];
    for (int i = 0; i < order; ++i) {
        coloursLF[i] = -1; // No colour at the beginning
    }

    int vertex;

    for (int i = 0; i < order; ++i) {

        for (int j = 0; j < maxDegree + 1; ++j) {
            visited[j] = false;
        }

        vertex = arr[i].id;

        // Mark the colors of adjacent vertices as unavailable
        for (int j = 0; j < adjMat[vertex].Size(); ++j) {
            int neighbour = adjMat[vertex].get(j) - 1;
            if (coloursLF[neighbour] != -1) {
                visited[coloursLF[neighbour] - 1] = true;
            }
        }

        // Find the first available color
        int color;
        for (color = 0; color < maxDegree + 1; ++color) {
            if (!visited[color]) {
                break;
            }
        }

        coloursLF[vertex] = color + 1;
    }

    for (int i = 0; i < order; ++i) {
        printf("%d ", coloursLF[i]);
    }

    delete[] visited;
    delete[] coloursLF;
}

Vector *adjMatAlloc(long long int order) {
    Vector *adjMat = new Vector[order];
    return adjMat;
}

void freeSpace(Vector *adjMat) {
    delete[] adjMat;
}

void printNotImplemented() {
    printf("\n?"); // vertices colours SLF
    printf("\n?"); // the number of different C4 subgraphs
}

void printAnswer(char &tmp) {
    long long int order = getGraphOrder(tmp);
    degreeSequence(order);
    printf("\n"); // endl after number of complements edges
}

int getNumber(char &tmp) {
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
#ifndef GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H
#define GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H

#include "iostream"
#include "Vector.h"

using namespace std;

struct Vertex_ID_AND_DEGREE{
    int id;
    int degree;
};

void merge(Vertex_ID_AND_DEGREE *arr, int firstIndex, int middleIndex, int lastIndex);

void mergeSort(Vertex_ID_AND_DEGREE *arr, int firstIndex, int lastIndex);

void merge2(Vertex_ID_AND_DEGREE *arr, int firstIndex, int middleIndex, int lastIndex);

void mergeSortIDS(Vertex_ID_AND_DEGREE *arr, int firstIndex, int lastIndex);

int getGraphOrder(char &tmp);

void degreeSequence(long long int order);

int countComponents(Vector *adjMat, long long int order, long long int& complementsEdges);

void dfs(Vector *adjMat, long long int order, int start, bool *visited, long long int& edges);

bool bipartite(Vector *adjMat, long long int order);

void bipartiteDFS(Vector *adjMat, long long int order, int start, bool *visited, int *bipartite);

void coloursGreedy(Vector *adjMat, long long int order, int maxDegree);

void coloursLF(Vector *adjMat, Vertex_ID_AND_DEGREE *arr, long long int order, int maxDegree);

Vector* adjMatAlloc(long long int order);

void freeSpace(Vector *adjMat);

void printNotImplemented();

void printAnswer(char &tmp);

int getNumber(char& tmp);

#endif //GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H
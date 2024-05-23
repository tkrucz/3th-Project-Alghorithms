#ifndef GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H
#define GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H

#include "iostream"
#include "Vector.h"

using namespace std;

bool compare(int num1, int num2);

void merge(int *arr, int firstIndex, int middleIndex, int lastIndex);

void mergeSort(int *arr, int firstIndex, int lastIndex);

int getGraphOrder(char &tmp);

void degreeSequence(long long int order);

int countComponents(Vector *adjMat, long long int order, long long int& complementsEdges);

void dfs(Vector *adjMat, long long int order, int start, bool *visited, long long int& edges);

bool bipartite(Vector *adjMat, long long int order);

void bipartiteDFS(Vector *adjMat, long long int order, int start, bool *visited, int *bipartite);

void coloursGreedy(Vector *adjMat, long long int order);

Vector* adjMatAlloc(long long int order);

void freeSpace(Vector *adjMat);

void printNotImplemented();

int getNumber(char& tmp);

#endif //GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H
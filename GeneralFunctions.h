#ifndef GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H
#define GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H

#include "iostream"
#include "Vector.h"

using namespace std;

bool compare(int num1, int num2);

void merge(int *arr, int firstIndex, int middleIndex, int lastIndex);

void mergeSort(int *arr, int firstIndex, int lastIndex);

int getGraphOrder(char &tmp);

void degreeSequence(int order);

int countComponents(Vector *adjMat, int order);

void dfs(Vector *adjMat, int order, int start, bool *visited);

bool bipartite(Vector *adjMat, int order); // TO DO!

void bipartiteDFS(Vector *adjMat, int order, int start, bool *visited, int *bipartite); // TO DO!

Vector* adjMatAlloc(int order);

void freeSpace(Vector *adjMat);

#endif //GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H
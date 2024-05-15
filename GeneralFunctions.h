#ifndef GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H
#define GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H

#include "iostream"

using namespace std;

bool compare(int num1, int num2);

void merge(int *arr, int firstIndex, int middleIndex, int lastIndex);

void mergeSort(int *arr, int firstIndex, int lastIndex);

int getGraphOrder(char &tmp, int &n);

void degreeSequence(char &tmp, int& n);

#endif //GRAPHS_3TH_PROJECT_GENERALFUNCTIONS_H
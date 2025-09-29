#include <stdlib.h>

#ifndef SORT_H
#define SORT_H

void printArray(int *arr, int n);
void heapsort(int *arr, int n);
void quicksort(int *arr, int p, int r);
void selectionSort(int *arr, int n);
void mergeSort(int *arr, int l, int r);

#endif
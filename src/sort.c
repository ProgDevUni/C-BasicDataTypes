#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void printArray(int *arr, int n) {
    for (int i=0;i<n;i++)
        printf("%d ", arr[i]);
    printf("\n");
}

static void heapify(int *arr, int n, int i) {
    int largest = i;
    int l = 2*i;
    int r = 2*i+1;

    if (l<n && arr[l] > arr[largest])
        largest  = l;
   
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}

void heapsort(int *arr, int n) {
    for (int i=n/2-1; i>=0; i--)
        heapify(arr, n, i);

    for (int i=n-1;i>0;i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

static int partion(int *arr, int p, int r) {
    int x = arr[r];
    int i = p-1;
    int temp;

    for (int j=p;j<=r-1;j++) {
        if (arr[j] <= x) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i+1];
    arr[i+1] = arr[r];
    arr[r] = temp;

    return i+1;
}

void quicksort(int *arr, int p, int r) {
    if (p < r) {
        int q = partion(arr, p, r);
        quicksort(arr, p, q-1);
        quicksort(arr, q+1, r);
    }
}

void selectionSort(int *arr, int n) {
    for (int i=0;i<n;i++) {
        int min = arr[i];
        int minIndex = i;
        for (int j=i+1;j<n;j++) {
            if (arr[j] < min) {
                min = arr[j];
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

static void merge(int *arr, int l, int m, int r) {
    int i,j,k;
    int n1 = m-l+1;
    int n2 = r-m;

    int L[n1], R[n2];

    for (i=0;i<n1;i++)
        L[i] = arr[l+i];
    for (j=0;j<n2;j++)
        R[j] = arr[m+1+j];

    i=0;
    j=0;
    k=l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }


    while (i<n1) {
        arr[k] = L[i];
        k++;
        i++;
    }

    while (j < n2) {
        arr[k] = R[j];
        k++;
        j++;
    }
}

void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = (l+r)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        
        merge(arr, l, m, r);
    }
}
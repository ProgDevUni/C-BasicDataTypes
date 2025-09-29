#include <stdlib.h>
#include "util.h"

int findMin(int *arr, int n) {
    int min = arr[0];
    for (int i=1;i<n;i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int findMax(int *arr, int n) {
    int max = arr[0];
    for (int i=1;i<n;i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int binarySearch(int *arr, int n, int goal) {
    int st = 0;
    int fn = n;
    while (st < fn) {
        int mid = (st+fn)/2;
        if (arr[mid] == goal) {return mid;}
        else if(arr[mid] > goal) {
            fn = mid;
        }
        else {
            st = mid+1;
        }
    }
    return -1;
}
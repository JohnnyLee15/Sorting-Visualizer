#include <stdlib.h>
#include "sort_logs.h"
#include "arrayFunctions.h"

#define SWAPS_INIT_SIZE 100

Swaps* createSwaps() {
    Swaps *newSwaps = malloc(sizeof(Swaps));
    if (newSwaps != NULL) {
        newSwaps->size = 0;
        newSwaps->cap = SWAPS_INIT_SIZE;
        newSwaps->data = malloc(newSwaps->cap * sizeof(Swap));

        if (newSwaps->data == NULL) {
            free(newSwaps);
            newSwaps = NULL;
        }
    }

    return newSwaps;
}

void destroySwaps(Swaps *swaps) {
    if (swaps != NULL) {
        free(swaps->data);
    }
    free(swaps);
}

void increaseSwapCap(Swaps *swaps) {
    if (swaps != NULL) {
        int newCap = swaps->cap * 2;
        Swap *newData = malloc(sizeof(Swap) * newCap);
        if (newData != NULL) {
            swaps->cap = newCap;
            for (int k = 0; k < swaps->size; k++) {
                newData[k].i = swaps->data[k].i;
                newData[k].j = swaps->data[k].j;
            }

            free(swaps->data);
            swaps->data = newData;
        }
    }
}

static void insertSwap(Swaps *swaps, int i, int j) {
    if (swaps != NULL) {
        if (swaps->size >= swaps->cap) {
            increaseSwapCap(swaps);
        }

        if (swaps->size < swaps->cap) {
            swaps->data[swaps->size].i = i;
            swaps->data[swaps->size].j = j;
            swaps->size++;
        }
    }
}

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void quicksort_internal_log(int *arr, int start, int end, Swaps *swaps) {
    if (start >= end - 1) 
        return; 

    int i = start;
    int pivot = arr[end - 1];

    for (int j = start; j < end - 1; j++) {
        if (arr[j] < pivot) {
            if (i != j) {
                swap(&arr[i], &arr[j]);
                insertSwap(swaps, i, j);
            }

            i++;
        }
    }

    if (i != end -1) {
        swap(&arr[i], &arr[end-1]);
        insertSwap(swaps, i, end-1);
    }

    quicksort_internal_log(arr, start, i, swaps);
    quicksort_internal_log(arr, i+1, end, swaps);
}

Swaps* quicksort_log(int *arr, int size) {
    Swaps *swaps = createSwaps();
    int *tempArr = copyArr(arr, size);
    if (tempArr == NULL || swaps == NULL) {
        destroySwaps(swaps);
        return NULL;
    }

    quicksort_internal_log(tempArr, 0, size, swaps);
    free(tempArr);
    return swaps;
}

static void bubblesort_internal_log(int *arr, int size, Swaps *swaps) {
    int i = 0;
    int swapped = 1;
    while (i < size - 1 && swapped) {
        swapped = 0;
        for (int j = 1; j < size - i; j++) {
            if (arr[j-1] > arr[j]) {
                swap(&arr[j], &arr[j-1]);
                insertSwap(swaps, j, j-1);
                swapped = 1;
            }
        }
        i++;
    } 
}

Swaps* bubblesort_log(int *arr, int size) {
    Swaps *swaps = createSwaps();
    int *tempArr = copyArr(arr, size);
    if (tempArr == NULL || swaps == NULL) {
        destroySwaps(swaps);
        return NULL;
    }

    bubblesort_internal_log(tempArr, size, swaps);
    free(tempArr);
    return swaps;
}
#include "arrayFunctions.h"
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int* randomIntArray(int size, int min, int max) {
    srand((unsigned) time(NULL));
    int range = max - min + 1;
    int *randArr = malloc(sizeof(int) * size);

    if (randArr != NULL) {
        for (int i = 0; i < size; i++) {
            randArr[i] = min + rand() % range;
        }
    }

    return randArr;
}

int getMax(int *arr, int size) {
    int max = INT_MIN;
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

int* copyArr(int *arr, int size) {
    int *copy = malloc(sizeof(int) * size);
    if (copy != NULL) {
        memcpy(copy, arr, size *sizeof(int));
    }

    return copy;
}
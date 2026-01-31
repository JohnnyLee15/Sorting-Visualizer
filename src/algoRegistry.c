#include "algoRegistry.h"
#include <string.h>

#define NUM_ALGOS 3

static const AlgoEntry ALGORITHMS[] = {
    {1, "Quick Sort", quicksort_log},
    {2, "Bubble Sort", bubblesort_log},
    {3, "Selection Sort", selectionsort_log}
};

SortLogger getAlgo(int algo) {
    for (int i = 0; i < NUM_ALGOS; i++) {
        if (algo == ALGORITHMS[i].id) {
            return ALGORITHMS[i].algo;
        }
    }
    return NULL;
}

const AlgoEntry* getAlgoDetails(int idx) {
    if (idx < NUM_ALGOS) {
        return &ALGORITHMS[idx];
    }

    return NULL;
}

int getAlgoCount() {
    return NUM_ALGOS;
}

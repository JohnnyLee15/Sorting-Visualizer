#include "algoRegistry.h"
#include <string.h>

#define NUM_ALGOS 3

typedef struct ALGO_ENTRY {
    const char *name;
    SortLogger algo;
} AlgoEntry;

static const AlgoEntry ALGORITHMS[] = {
    {"quicksort", quicksort_log},
    {"bubblesort", bubblesort_log},
    {"selectionsort", selectionsort_log}
};

SortLogger getAlgo(const char *name) {
    for (int i = 0; i < NUM_ALGOS; i++) {
        if (strcmp(name, ALGORITHMS[i].name) == 0) {
            return ALGORITHMS[i].algo;
        }
    }
    return NULL;
}
#ifndef ALGO_REG
#define ALGO_REG

#include "sort_logs.h"
typedef Events* (*SortLogger)(int *arr, int size);
typedef struct ALGO_ENTRY {
    int id;
    const char *name;
    SortLogger algo;
} AlgoEntry;

SortLogger getAlgo(int algo);
const AlgoEntry* getAlgoDetails(int idx);
int getAlgoCount();

#endif
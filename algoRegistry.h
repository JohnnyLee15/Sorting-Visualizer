#ifndef ALGO_REG
#define ALGO_REG

#include "sort_logs.h"

typedef Swaps* (*SortLogger)(int *arr, int size);
SortLogger getAlgo(const char *name);

#endif
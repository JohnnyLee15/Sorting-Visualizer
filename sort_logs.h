#ifndef SORT
#define SORT

typedef struct SWAP {
    int i;
    int j;
} Swap;

typedef struct SWAPS {
    Swap *data;
    int size;
    int cap;
} Swaps;

Swaps* createSwaps();
void destroySwaps(Swaps*);

Swaps* quicksort_log(int *arr, int size);

#endif
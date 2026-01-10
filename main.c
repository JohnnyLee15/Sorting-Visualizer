#include "visualizer.h"
#include "algoRegistry.h"
#include <stdio.h>

#define MIN 1
#define MAX 10000
#define SIZE 2000

int main(int argc, char **argv) {
    const char *name = (argc != 2) ? "quicksort" : argv[1]; 
    SortLogger algo = getAlgo(name);

    if (algo == NULL) {
        printf("Unknown sorting algorithm: %s\n", name);
        return 1;
    }

    runVisualizer(MIN, MAX, SIZE, algo);
    return 0;
}
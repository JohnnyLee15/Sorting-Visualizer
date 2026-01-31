#include "menu.h"
#include "algoRegistry.h"
#include <stdio.h>
#include <stdlib.h>

#define TAB_SPACES 4
#define INPUT_BUF 256

void showMenu() {
    int numAlgos = getAlgoCount();
    printf("\nSorting Algorithm Visualizer\n");
    printf("----------------------------\n");

    for (int i = 0; i < numAlgos; i++) {
        const AlgoEntry *details = getAlgoDetails(i);
        printf("%*s[%d] %s\n", TAB_SPACES, "", details->id, details->name);
    }
}

int selectAlgo() {
    char buf[INPUT_BUF];
    char *end;
    printf("\nSelect an algorithm (0 to quit): ");

    if (!fgets(buf, INPUT_BUF, stdin)) {
        return -1;
    }

    long choice = strtol(buf, &end, 10);

    if (end == buf) {
        return - 1;
    }

    if (choice >= 0 && choice <= getAlgoCount()) {
        return (int) choice;
    }
    
    return -1;
}
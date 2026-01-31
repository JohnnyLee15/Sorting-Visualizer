#include "visualizer.h"
#include "menu.h"
#include <stdio.h>

#define MIN 1
#define MAX 1000
#define SIZE 250

int main() {

    int choice = -1;
    while (choice != QUIT) {
        showMenu();
        choice = selectAlgo();
        if (choice != -1 && choice != QUIT) {

            SortLogger algo = getAlgo(choice);
            if (algo == NULL) {
                printf("\nInternal error: Invalid algorithm %d.\n", choice);
            } else {
                runVisualizer(MIN, MAX, SIZE, algo);
            }
        } else if (choice == -1) {
            printf("\nError: Invalid selection.\n");
        }
    }
    return 0;
}
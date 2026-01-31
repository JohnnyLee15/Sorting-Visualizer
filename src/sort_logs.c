#include <stdlib.h>
#include "sort_logs.h"
#include "arrayFunctions.h"

#define SWAPS_INIT_SIZE 100

Events* createEvents() {
    Events *newEvents = malloc(sizeof(Events));
    if (newEvents != NULL) {
        newEvents->size = 0;
        newEvents->cap = SWAPS_INIT_SIZE;
        newEvents->data = malloc(newEvents->cap * sizeof(Event));

        if (newEvents->data == NULL) {
            free(newEvents);
            newEvents = NULL;
        }
    }

    return newEvents;
}

void destroyEvents(Events *events) {
    if (events != NULL) {
        free(events->data);
    }
    free(events);
}

void increaseEventCap(Events *events) {
    if (events != NULL) {
        int newCap = events->cap * 2;
        Event *newData = malloc(sizeof(Event) * newCap);
        if (newData != NULL) {
            events->cap = newCap;
            for (int k = 0; k < events->size; k++) {
                newData[k].i = events->data[k].i;
                newData[k].j = events->data[k].j;
                newData[k].type = events->data[k].type;
            }

            free(events->data);
            events->data = newData;
        }
    }
}

static void insertEvent(Events *events, int i, int j, EventType type) {
    if (events != NULL) {
        if (events->size >= events->cap) {
            increaseEventCap(events);
        }

        if (events->size < events->cap) {
            events->data[events->size].i = i;
            events->data[events->size].j = j;
            events->data[events->size].type = type;
            events->size++;
        }
    }
}

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void quicksort_internal_log(int *arr, int start, int end, Events *events) {
    if (start >= end - 1) 
        return; 

    int i = start;
    int pivot = arr[end - 1];

    for (int j = start; j < end - 1; j++) {
        insertEvent(events, j, end - 1, COMPARE);
        if (arr[j] < pivot) {
            if (i != j) {
                swap(&arr[i], &arr[j]);
                insertEvent(events, i, j, SWAP);
            }

            i++;
        }
    }

    if (i != end -1) {
        swap(&arr[i], &arr[end-1]);
        insertEvent(events, i, end-1, SWAP);
    }

    quicksort_internal_log(arr, start, i, events);
    quicksort_internal_log(arr, i+1, end, events);
}

Events* quicksort_log(int *arr, int size) {
    Events *events = createEvents();
    int *tempArr = copyArr(arr, size);
    if (tempArr == NULL || events == NULL) {
        destroyEvents(events);
        return NULL;
    }

    quicksort_internal_log(tempArr, 0, size, events);
    free(tempArr);
    return events;
}

static void bubblesort_internal_log(int *arr, int size, Events *events) {
    int i = 0;
    int swapped = 1;
    while (i < size - 1 && swapped) {
        swapped = 0;
        for (int j = 1; j < size - i; j++) {
            insertEvent(events, j, j-1, COMPARE);
            if (arr[j-1] > arr[j]) {
                swap(&arr[j], &arr[j-1]);
                insertEvent(events, j, j-1, SWAP);
                swapped = 1;
            }
        }
        i++;
    } 
}

Events* bubblesort_log(int *arr, int size) {
    Events *events = createEvents();
    int *tempArr = copyArr(arr, size);
    if (tempArr == NULL || events == NULL) {
        destroyEvents(events);
        return NULL;
    }

    bubblesort_internal_log(tempArr, size, events);
    free(tempArr);
    return events;
}

static void selectionsort_internal_log(int *arr, int size, Events *events) {
    for (int end = size - 1; end > 0; end--) {
        int maxIdx = 0;

        for (int i = 1; i <=end; i++) {
            insertEvent(events, i, maxIdx, COMPARE);
            if (arr[i] > arr[maxIdx]) {
                maxIdx = i;
            }
        }

        if (maxIdx != end) {
            swap(&arr[maxIdx], &arr[end]);
            insertEvent(events, maxIdx, end, SWAP);
        }
    }
}

Events* selectionsort_log(int *arr, int size) {
    Events *events = createEvents();
    int *tempArr = copyArr(arr, size);
    if (tempArr == NULL || events == NULL) {
        destroyEvents(events);
        return NULL;
    }

    selectionsort_internal_log(tempArr, size, events);
    free(tempArr);
    return events;
}

static void insertionsort_internal_log(int *arr, int size, Events *events) {
    for (int i = 1; i < size; i++) {
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j]) {
            insertEvent(events, j - 1, j, COMPARE);

            swap(&arr[j - 1], &arr[j]);
            insertEvent(events, j - 1, j, SWAP);
            
            j--;
        }

        if (j > 0) {
            insertEvent(events, j - 1, j, COMPARE);
        }
    }
}

Events* insertionsort_log(int *arr, int size) {
    Events *events = createEvents();
    int *tempArr = copyArr(arr, size);
    if (tempArr == NULL || events == NULL) {
        destroyEvents(events);
        return NULL;
    }

    insertionsort_internal_log(tempArr, size, events);
    free(tempArr);
    return events;
}
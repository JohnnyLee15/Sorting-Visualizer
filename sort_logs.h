#ifndef SORT
#define SORT

typedef enum EVENT_TYPE {
    COMPARE,
    SWAP,
    NONE
} EventType;

typedef struct EVENT {
    int i;
    int j;
    EventType type;
} Event;

typedef struct EVENTS {
    Event *data;
    int size;
    int cap;
} Events;

Events* createEvents();
void destroyEvents(Events*);

Events* quicksort_log(int *arr, int size);
Events* bubblesort_log(int *arr, int size);
Events* selectionsort_log(int *arr, int size);

#endif
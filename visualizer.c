#include "visualizer.h"
#include "sort_logs.h"
#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "arrayFunctions.h"

#define WINDOW_WIDTH 1920
#define VIRTUAL_WIDTH 3000
#define WINDOW_HEIGHT 900
#define TOP_MARGIN 50
#define HORIZONTAL_MARGIN 30
#define FRAME_PER_SWAP 5
#define FRAME_PER_COMP 1
#define FRAME_DELAY_COMPLETED 2

static Color getColor(
    int completed, 
    int idx, 
    int eventIdx1, 
    int eventIdx2,
    EventType type
) {
    Color color;
    if (completed > 0 && idx < completed) {
        color = WHITE;
    } else if ((type == COMPARE) && (idx == eventIdx1 || idx == eventIdx2)){
        color = BLUE;
    } else if ((idx == eventIdx1 || idx == eventIdx2) && (type == SWAP)) {
        color = RED;
    } else {
        color = GREEN;
    }

    return color;
}

static void drawRectangles(
    int *arr, 
    int size, 
    int eventIdx1, 
    int eventIdx2, 
    int completed,
    EventType type,
    int compCount,
    int swapCount
) {
    int maxVal = getMax(arr, size);
    maxVal = (maxVal == 0) ? 1 : maxVal;
    double heightScale = (WINDOW_HEIGHT - TOP_MARGIN) / (double) maxVal;
    double widthScale = WINDOW_WIDTH / (double) VIRTUAL_WIDTH;
    double virtualBarWidth = (VIRTUAL_WIDTH- 2*HORIZONTAL_MARGIN) / (double) size;
    int barWidth = virtualBarWidth * widthScale;
    int width = (barWidth < 1) ? 1 : barWidth;

    BeginDrawing();
    ClearBackground(BLACK);
    DrawText(TextFormat("Comparisons: %d", compCount), 10, 30, 20, WHITE);
    DrawText(TextFormat("Swaps: %d", swapCount),       10, 55, 20, WHITE);

    for (int i = 0; i < size; i++) {
        int height = arr[i] * heightScale;
        int gap = (width > 1) ? 1 : 0;
        int x = (HORIZONTAL_MARGIN + i * virtualBarWidth) * widthScale;
        int y = WINDOW_HEIGHT - height;

        Color color = getColor(completed, i, eventIdx1, eventIdx2, type);

        DrawRectangle(x, y, width - gap, height, color);
    }
    DrawFPS(10, 10);
    EndDrawing();
}

static void swap(int *arr, Events *events, int k) {
    if (k < events->size) {
        Event eventPair = events->data[k];
        int temp = arr[eventPair.i];
        arr[eventPair.i] = arr[eventPair.j];
        arr[eventPair.j] = temp;
    }
}

static void setEventIndices(int *idx1, int *idx2, int curr, Events *events, EventType *type) {
    if (curr < events->size) {
        *idx1 = events->data[curr].i;
        *idx2 = events->data[curr].j;
        *type = events->data[curr].type;
    }
}

static void prepFrame(
    int *arr, 
    int *frames, 
    int *curr, 
    Events *events, 
    int *completedFrames, 
    int *completed, 
    int size,
    int *compCount,
    int *swapCount
) {
    if (*curr < events->size) {
        EventType type = events->data[*curr].type;
        (*frames)++;
        int period = (type == SWAP) ? FRAME_PER_SWAP : FRAME_PER_COMP;

        if (*frames >= period) {
            if (type == SWAP) {
                swap(arr, events, *curr);
                (*swapCount)++;
            } else if (type == COMPARE) {
                (*compCount)++;
            }
            (*curr)++;
            *frames = 0;
        }

    } else {
        (*completedFrames)++;
        if (*completedFrames % FRAME_DELAY_COMPLETED == 0 && *completed < size) {
            (*completed)++;
        }
    }
}

static void cleanUpVisualizer(Events *events, int *arr) {
    CloseWindow();
    free(arr);
    destroyEvents(events);
}

void runVisualizer(int min, int max, int size, SortLogger sortAlgo) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sorting");
    SetTargetFPS(240);

    int *arr = randomIntArray(size, min, max);
    Events *events = sortAlgo(arr, size);
    if (events == NULL) {
        cleanUpVisualizer(events, arr);
        return;
    }
        
    int curr = 0;
    int completed = 0;
    int frames = 0;
    int completedFrames = 0;
    int swapCount = 0;
    int compCount = 0;

    while (!WindowShouldClose()) {
        int eventIdx1 = -1;
        int eventIdx2 = -1;
        EventType type = NONE;

        setEventIndices(&eventIdx1, &eventIdx2, curr, events, &type);
        drawRectangles(arr, size, eventIdx1, eventIdx2, completed, type, compCount, swapCount);
        prepFrame(arr, &frames, &curr, events, &completedFrames, &completed, size, &compCount, &swapCount);

    }
    cleanUpVisualizer(events, arr);
}
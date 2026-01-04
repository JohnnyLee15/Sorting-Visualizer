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
#define FRAME_PER_SWAP 1
#define FRAME_DELAY_COMPLETED 1

static Color getColor(int completed, int idx, int swapIdx1, int swapIdx2) {
    Color color;
    if (completed > 0 && idx < completed) {
        color = WHITE;
    } else if (idx == swapIdx1 || idx == swapIdx2) {
        color = RED;
    } else {
        color = GREEN;
    }

    return color;
}

static void drawRectangles(int *arr, int size, int swapIdx1, int swapIdx2, int completed) {
    int maxVal = getMax(arr, size);
    maxVal = (maxVal == 0) ? 1 : maxVal;
    double heightScale = (WINDOW_HEIGHT - TOP_MARGIN) / (double) maxVal;
    double widthScale = WINDOW_WIDTH / (double) VIRTUAL_WIDTH;
    double virtualBarWidth = (VIRTUAL_WIDTH- 2*HORIZONTAL_MARGIN) / (double) size;
    int barWidth = virtualBarWidth * widthScale;
    int width = (barWidth < 1) ? 1 : barWidth;

    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < size; i++) {
        int height = arr[i] * heightScale;
        int gap = (width > 1) ? 1 : 0;
        int x = (HORIZONTAL_MARGIN + i * virtualBarWidth) * widthScale;
        int y = WINDOW_HEIGHT - height;

        Color color = getColor(completed, i, swapIdx1, swapIdx2);

        DrawRectangle(x, y, width - gap, height, color);
    }
    DrawFPS(10, 10);
    EndDrawing();
}

static void swap(int *arr, Swaps *swaps, int k) {
    if (k < swaps->size) {
        Swap swapPair = swaps->data[k];
        int temp = arr[swapPair.i];
        arr[swapPair.i] = arr[swapPair.j];
        arr[swapPair.j] = temp;
    }
}

static void setSwapIndices(int *idx1, int *idx2, int curr, Swaps *swaps) {
    if (curr < swaps->size) {
        *idx1 = swaps->data[curr].i;
        *idx2 = swaps->data[curr].j;
    }
}

static void prepFrame(
    int *arr, 
    int *frames, 
    int *curr, 
    Swaps *swaps, 
    int *completedFrames, 
    int *completed, 
    int size
) {
    (*frames)++;
    if (*curr < swaps->size) {
        if (*frames % FRAME_PER_SWAP == 0) {
            swap(arr, swaps, *curr);
            (*curr)++;
        }

    } else {
        (*completedFrames)++;
        if (*completedFrames % FRAME_DELAY_COMPLETED == 0 && *completed < size) {
            (*completed)++;
        }
    }
}

void runVisualizer(int min, int max, int size) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sorting");

    int *arr = randomIntArray(size, min, max);
    Swaps *swaps = quicksort_log(arr, size);
    int curr = 0;
    int completed = 0;
    int frames = 0;
    int completedFrames = 0;

    while (!WindowShouldClose()) {
        int swapIdx1 = -1;
        int swapIdx2 = -1;

        setSwapIndices(&swapIdx1, &swapIdx2, curr, swaps);
        drawRectangles(arr, size, swapIdx1, swapIdx2, completed);
        prepFrame(arr, &frames, &curr, swaps, &completedFrames, &completed, size);

    }

    CloseWindow();
    free(arr);
    destroySwaps(swaps);
}
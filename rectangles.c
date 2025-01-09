#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"

// clang flags: -lraylib
#define WINDOW_WIDTH    800
#define WINDOW_HEIGHT   600

#define MARGIN_WIDTH    100
#define MARGIN_HEIGHT   100

#define BAR_SEPARATION  1

#define MAX_BAR_COUNT   139

Color COLORS[] = { RED, BLUE, GREEN, WHITE, GRAY, YELLOW, BROWN, PINK, SKYBLUE, ORANGE };
size_t N_COLORS = sizeof(COLORS) / sizeof(Color);

void drawBars(int xStart, int recWidth, int yLimit, List *recHeights, List *colors);
void addHeight(List *recHeights, List *colors);
void removeHeight(List *recHeights, List *colors);

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rectangles");
    SetTargetFPS(60);
    InitAudioDevice();

    srand((unsigned int)time(NULL));

    int myArray[] = { 100, 500, 300 };
    int myColors[] = { 0, 0, 0 };

    size_t nBars = sizeof(myArray) / sizeof(myArray[0]);

    List *heights = newList(myArray, nBars);
    List *colors = newList(myColors, nBars);

    int xStart = MARGIN_WIDTH / 2;
    int yLimit = WINDOW_HEIGHT - (MARGIN_HEIGHT / 2);

    // int xFinal = WINDOW_WIDTH - xStart;

    while (!WindowShouldClose())
    {
        int recWidth = ((WINDOW_WIDTH - MARGIN_WIDTH) / heights->count) - BAR_SEPARATION; // nBars = 1 pixel of separation

        if (IsKeyDown(KEY_ESCAPE))
            break;

        if (IsKeyDown(KEY_RIGHT))  
            addHeight(heights, colors);

        if (IsKeyDown(KEY_LEFT))
            removeHeight(heights, colors);
        
        BeginDrawing();

        drawBars(xStart, recWidth, yLimit, heights, colors);

        ClearBackground(BLACK);

        EndDrawing();
    }

    freeList(heights); 
    freeList(colors);
    CloseAudioDevice();

    CloseWindow();
}

void drawBars(int xStart, int recWidth, int yLimit, List *recHeights, List *colors)
{
    int xRec = xStart;
    for (size_t i = 0; i < recHeights->count; ++i)
    {   
        int recHeight = recHeights->vals[i] <= yLimit ? recHeights->vals[i] : yLimit;
        int yRec = (yLimit - recHeight) + MARGIN_HEIGHT / 2;

        DrawRectangle(xRec, yRec, recWidth, recHeight, COLORS[colors->vals[i]]);

        if (i < recHeights->count - 1) 
            xRec++;
        xRec += recWidth;
    }
}

void addHeight(List *recHeights, List *colors)
{
    if (recHeights->count > MAX_BAR_COUNT)
        return;

    int newHeight = rand() % (WINDOW_HEIGHT - 0 + 1) + 0;

    size_t iColor = rand() % (N_COLORS - 0) + 0;

    pushBackList(recHeights, newHeight);
    pushBackList(colors, iColor);
}

void removeHeight(List *recHeights, List *colors)
{
    popBackList(recHeights);
    popBackList(colors);
}
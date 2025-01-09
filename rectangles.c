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


void drawBars(int xStart, int recWidth, int yLimit, List *recHeights);
void addHeight(List *list);
void removeHeight(List *list);

// TODO:
// Fix X margins
int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rectangles");
    SetTargetFPS(60);

    srand((unsigned int)time(NULL));

    int myArray[] = { 100, 500, 300 };
    size_t nBars = sizeof(myArray) / sizeof(myArray[0]);

    List *heights = newList(myArray, nBars);

    int xStart = MARGIN_WIDTH / 2;
    int yLimit = WINDOW_HEIGHT - (MARGIN_HEIGHT / 2);

    // int xFinal = WINDOW_WIDTH - xStart;

    while (!WindowShouldClose())
    {
        int recWidth = ((WINDOW_WIDTH - MARGIN_WIDTH) / heights->count) - BAR_SEPARATION; // nBars = 1 pixel of separation

        if (IsKeyDown(KEY_ESCAPE))
            break;

        if (IsKeyDown(KEY_RIGHT))  
            addHeight(heights);

        if (IsKeyDown(KEY_LEFT))
            removeHeight(heights);
        
        BeginDrawing();

        drawBars(xStart, recWidth, yLimit, heights);

        ClearBackground(BLACK);

        EndDrawing();
    }

    freeList(heights); 

    CloseWindow();
}

void drawBars(int xStart, int recWidth, int yLimit, List *recHeights)
{
    int xRec = xStart;
    for (size_t i = 0; i < recHeights->count; ++i)
    {   
        int recHeight = recHeights->vals[i] <= yLimit ? recHeights->vals[i] : yLimit;
        int yRec = (yLimit - recHeight) + MARGIN_HEIGHT / 2;

        DrawRectangle(xRec, yRec, recWidth, recHeight, RED);

        if (i < recHeights->count - 1) 
            xRec++;
        xRec += recWidth;
    }
}

void addHeight(List *list)
{
    int newHeight = rand() % (WINDOW_HEIGHT - 0 + 1) + 0;

    pushBackList(list, newHeight);
}

void removeHeight(List *list)
{
    popBackList(list);
}
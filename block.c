#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH    400
#define WINDOW_HEIGHT   400

#define SNAKE_SIZE      20
#define PILL_RADIUS     5

void handleError(const char *message)
{
    perror(message);
    exit(1);
}

typedef struct Entity {
    int x;
    int y;
    int width;
    int height;
    int velocity;
    Color color;
} Entity;

Entity *createEntity(int x, int y, int velocity, int width, int height, Color color)
{
    Entity *entity;
    entity = (Entity *)malloc(sizeof(Entity));
    if (entity == NULL)
        handleError("Error allocating memory for Entity");
    
    entity->x = x;
    entity->y = y;
    entity->width = width;
    entity->height = height;
    entity->velocity = velocity;
    entity->color = color;

    return entity;
}

Rectangle getCollisionRect(Entity *entity)
{
    Rectangle rectangle;
    rectangle.x = (float)entity->x;
    rectangle.y = (float)entity->y;
    rectangle.width = (float)entity->width;
    rectangle.height = (float)entity->height;

    return rectangle;
}

void freeEntity(Entity *entity)
{
    free(entity);
}

int getRandomPosition(int min, int max) 
{
    return rand() % (max - min + 1) + min;
}

void spawnPill(Entity *pill)
{
    srand(time(NULL));
    pill->x = getRandomPosition(0, WINDOW_WIDTH - PILL_RADIUS);  
    pill->y = getRandomPosition(0, WINDOW_HEIGHT - PILL_RADIUS);
}

void upgradeBlock(Entity *block)
{
    block->velocity += 1;
}

void pickupPill(Entity *pill, Entity *block)
{
    spawnPill(pill);
    upgradeBlock(block);
}

int main()
{
    Entity *block = createEntity(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1, SNAKE_SIZE, SNAKE_SIZE, WHITE);
    Entity *pill = createEntity(0, 0, 0, PILL_RADIUS, PILL_RADIUS, WHITE);

    spawnPill(pill);

    Color green = {20, 160, 133, 255};

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Block");
    Image windowIcon = LoadImage("assets/img/blue-mymy.png");
    SetWindowIcon(windowIcon);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        if (IsKeyDown(KEY_RIGHT) && block->x + block->velocity + SNAKE_SIZE <= WINDOW_WIDTH)
            block->x += block->velocity;
        else if (IsKeyDown(KEY_LEFT) && block->x - block->velocity >= 0)
            block->x -= block->velocity;
        else if (IsKeyDown(KEY_UP) && block->y - block->velocity >= 0)
            block->y -= block->velocity;
        else if (IsKeyDown(KEY_DOWN) && block->y + block->velocity + SNAKE_SIZE <= WINDOW_HEIGHT)
            block->y += block->velocity;

        if (CheckCollisionRecs(getCollisionRect(block), getCollisionRect(pill)))
            pickupPill(pill, block);

        BeginDrawing();
        
        ClearBackground(green);

        DrawRectangle(block->x, block->y, block->width, block->height, block->color);
        DrawCircle(pill->x, pill->y, pill->width, pill->color);

        EndDrawing();
    }

    CloseWindow();

    freeEntity(block);
    freeEntity(pill);

    return 0;
}
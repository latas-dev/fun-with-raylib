#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void handleError(char *error)
{
    fprintf( stderr, "%s", error );
    exit(-1);
}

List *newList(int *array, size_t n)
{
    List *newList;
    newList = (List *)malloc(sizeof(List));
    if (newList == NULL)
        handleError("Error allocating memory for newList");

    newList->count = n;
    newList->capacity = n * 2;

    newList->vals = (int *)calloc(newList->capacity, sizeof(int));

    for (size_t i = 0; i < n; ++i)
    {
        newList->vals[i] = array[i];
    }

    return newList;
}

void freeList(List *list)
{
    free(list->vals);
    free(list);
}

void pushBackList(List *list, int val)
{
    size_t newCount = list->count + 1;

    if (newCount > list->capacity)
    {
        int *temp = (int *)malloc(newCount * sizeof(int));
        if (temp == NULL)
            handleError("Error allocating temporary memory for List");

        memcpy(temp, list->vals, newCount * sizeof(int));

        list->capacity *= 2;

        list->vals = (int *)realloc(list->vals, list->capacity * sizeof(int));
        if (list->vals == NULL)
            handleError("Error reallocating memory for List");
    }

    list->vals[list->count] = val;
    list->count = newCount;
}

int popBackList(List *list)
{
    size_t newCount = list->count - 1;

    if (newCount <= 0)
        return 0;

    int popped = list->vals[newCount];
    list->vals[newCount] = 0;
    list->count = newCount;

    return popped;
}
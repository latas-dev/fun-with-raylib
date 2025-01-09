typedef struct {
    int *vals;
    size_t count;
    size_t capacity;
} List;

void handleError(char *error);

List *newList(int *array, size_t n);
void freeList(List *list);
void pushBackList(List *list, int val);
int popBackList(List *list);
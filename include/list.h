#include <stdbool.h>

#ifndef LIST_H
#define LIST_H

typedef struct Node {
    struct Node* prev;
    int value;
    struct Node* next;
} Node;

typedef struct List{
    Node* head;
    int size;
} List;

void initList(List *list);
void freeList(List *list);
bool list_isEmpty(List *list);
int list_getSize(List *list);

void list_pushFront(List *list, int value);
void list_pushBack(List *list, int value);
void list_insertAt(List *list, int index, int value);

void list_removeFront(List *list);
void list_removeBack(List *list);
void list_removeAt(List *list, int index);

int list_getFront(List *list);
int list_getBack(List *list);
int list_getAt(List *list, int index);

int list_find(List *list, int value); // returns index
bool list_contains(List *list, int value);
void list_printListForward(List *list);
void list_printListBackward(List *list);
void list_reverseList(List *list);

#endif 
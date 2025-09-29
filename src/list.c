#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "list.h"

void initList(List *list) {
    if (list == NULL) return;
    list->head = NULL;
    list->size = 0;
}

void freeList(List *list) {
    if (list == NULL) return;

    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->size = 0;

    free(list);
}

bool list_isEmpty(List *list) {
    if (list == NULL) return false;
    if (list->head == NULL && list->size==0) return true;
    return false;
}

int list_getSize(List *list) {
    if (list == NULL) return -1;
    return list->size;
}

void list_pushFront(List *list, int value){
    // we change head
    if (list == NULL) return;
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->value = value;
    list->size++;
    if (list->head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        list->head = newNode;
    }else {
        newNode->next = list->head;
        newNode->prev = list->head->prev;
        list->head->prev->next = newNode;
        list->head->prev = newNode;
        list->head = newNode;
    }
}
void list_pushBack(List *list, int value){
    // add value to tail
    if (list == NULL) return;
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->value = value;
    list->size++;
    if (list->head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        list->head = newNode;
    }else {
        newNode->next = list->head;
        newNode->prev = list->head->prev;

        list->head->prev->next = newNode;
        list->head->prev = newNode;
    }
}

void list_insertAt(List *list, int index, int value) {
    if (list == NULL) return;
    if (index > list->size) return; 

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;

    if (list->head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        list->head = newNode;
    } else {
        struct Node* node = list->head;
        for (int i = 0; i < index; i++)
            node = node->next;

        newNode->next = node;
        newNode->prev = node->prev;
        node->prev->next = newNode;
        node->prev = newNode;

        if (index == 0) {
            list->head = newNode;
        }
    }

    list->size++;
}


void list_removeFront(List *list){
    if (list == NULL || list->head == NULL) return;
    struct Node* h = list->head;
    if (list->size == 1) {
        free(h);
        list->head = NULL;
    }else {
        h->prev->next = h->next;
        h->next->prev = h->prev;
        list->head = h->next;
        free(h);
    }

    list->size--;
}
void list_removeBack(List *list){
    if (list == NULL || list->head == NULL) return;
    struct Node* t = list->head->prev;
    
    if (list->size == 1) {
        free(t);
        list->head = NULL;
    } else {
        t->prev->next = list->head;
        list->head->prev = t->prev;
        free(t);
    }

    list->size--;
}
void list_removeAt(List *list, int index){
    if (list == NULL) return;
    if (list->size == 1) {
        list->head = NULL;
        list->size = 0;
    }
    else {
        if (index >= list->size) return;
        struct Node* node = list->head;
        for (int i=0;i<index;i++)
            node=node->next;

        node->next->prev = node->prev;
        node->prev->next = node->next;
        free(node);
        list->size--;
    }    
}

int list_getFront(List *list){
    return list->head->value;
}
int list_getBack(List *list){
    return list->head->prev->value;
}
int list_getAt(List *list, int index){
    struct Node* node = list->head;
    for (int i=0;i<index;i++)
        node=node->next;
    return node->value;
}

int list_find(List *list, int value){
    if (list == NULL) return -1;
    struct Node* node = list->head;
    for (int i=0;i<list->size;i++) {
        if (node->value == value) {
            return i;
        }
        node = node->next;
    }
    return -1;
} 
bool list_contains(List *list, int value){
    if (list == NULL) return false;
    struct Node* node = list->head;
    for (int i=0;i<list->size;i++) {
        if (node->value == value) {
            return true;
        }
        node = node->next;
    }
    return false;
}
void list_printListForward(List *list){
    struct Node* node = list->head;
    for (int i=0;i<list->size; i++) {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}
void list_printListBackward(List *list){
    struct Node* node = list->head->prev;
    for (int i=0;i < list->size; i++) {
        printf("%d ", node->value);
        node = node->prev;
    }
    printf("\n");
}


/*
void testRun() {
    List list;
    initList(&list);

    // 1. list_isEmpty
    assert(list_isEmpty(&list));
    assert(list_getSize(&list) == 0);
    printf("First test compelete\n");

    // 2. pushFront
    list_pushFront(&list, 10);
    assert(!list_isEmpty(&list));
    assert(list_getSize(&list) == 1);
    assert(list_getFront(&list) == 10);
    assert(list_getBack(&list) == 10);
    printf("Second test compelete\n");

    // 3. pushBack
    list_pushBack(&list, 20);
    assert(list_getSize(&list) == 2);
    assert(list_getFront(&list) == 10);
    assert(list_getBack(&list) == 20);
    printf("Third test compelete\n");

    // 4. insertAt
    list_insertAt(&list, 1, 15); // insert in middle
    assert(list_getSize(&list) == 3);
    assert(list_getAt(&list, 1) == 15);
    printf("Fourth test compelete\n");

    // 5. find / contains
    assert(list_find(&list, 15) == 1);
    assert(list_contains(&list, 20));
    assert(!list_contains(&list, 999));
    printf("5th test compelete\n");

    // 6. removeFront
    list_removeFront(&list); // remove 10
    assert(list_getFront(&list) == 15);
    assert(list_getSize(&list) == 2);
    printf("6th test compelete\n");

    // 7. removeBack
    list_removeBack(&list); // remove 20
    assert(list_getBack(&list) == 15);
    assert(list_getSize(&list) == 1);
    printf("7th test compelete\n");

    // 8. removeAt
    list_pushBack(&list, 30);
    list_pushBack(&list, 40);
    list_removeAt(&list, 1); // remove 30
    assert(list_getSize(&list) == 2);
    assert(list_getAt(&list, 0) == 15);
    assert(list_getAt(&list, 1) == 40);
    printf("8th test compelete\n");

    // 9. Print forward/backward
    printf("List forward:   ");
    list_printListForward(&list);
    printf("List backward:  ");
    list_printListBackward(&list);
    printf("9th test compelete\n");

    printf("\nAll tests passed!\n");
}
*/
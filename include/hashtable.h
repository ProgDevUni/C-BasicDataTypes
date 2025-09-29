#include <stdlib.h>
#include <stdbool.h>

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef enum {EMPTY, OCCPUIED, DELETED} StatusSlot;

typedef struct Entry {
    int key;
    int value;
    StatusSlot slot;
} Entry;

typedef struct HashTable{
    int capacity;
    Entry* buckets;
} HashTable;

void initHashTable(HashTable* table);
void freeHashTable(HashTable* table);

void hashtable_insert(HashTable* table, int key, int value);
bool hashtable_find(HashTable* table, int key, int* outValue);
void hashtable_delete(HashTable* table, int key);

bool hashtable_contains(HashTable* table, int key);
void printHashTable(HashTable* table);

int hashtable_size(HashTable* table);
bool hashtable_isEmpty(HashTable* table);

#endif
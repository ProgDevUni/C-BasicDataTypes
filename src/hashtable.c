#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "hashtable.h"

static int h2(int k, int m) {
    return 1 + (k%m);
}

static int h1(int k, int m) {
    return k%m;
}

static int hash(int k, int i, int m) {
    return (h1(k, m) + i*h2(k, m-1))%m;
}

void initHashTable(HashTable* table) {
    if (table ==  NULL) return;
    table->capacity = 10;
    
    table->buckets = malloc(sizeof(Entry)*table->capacity);
    for (int i=0;i < table->capacity; i++) {
        table->buckets[i].key = NULL;
        table->buckets[i].value = NULL;
        table->buckets[i].slot = EMPTY;
    }
}
void freeHashTable(HashTable* table) {
    if (table == NULL) return;

    if (table->buckets != NULL) {
        free(table->buckets);
        table->buckets = NULL;
    }

    free(table);
}

static void resizeHashTable(HashTable* table, int newCapacity) {
    if (table == NULL) return;
    Entry* newBuckets = malloc(sizeof(Entry)*newCapacity);
    for (int i=0;i<newCapacity;i++) {
        newBuckets[i].key = NULL;
        newBuckets[i].value = NULL;
        newBuckets[i].slot = EMPTY;
    }

    Entry* oldBuckets = table->buckets;
    int oldCapacity = table->capacity;

    table->buckets = newBuckets;
    table->capacity = newCapacity;
    for (int i=0;i<oldCapacity;i++) {
        if (oldBuckets[i].slot == OCCPUIED) {
            hashtable_insert(table, oldBuckets[i].key, oldBuckets[i].value);
        }
    }

    free(oldBuckets);
}

void hashtable_insert(HashTable* table, int key, int value) {
    if (table == NULL) return;
    for (int i=0;i < table->capacity; i++) {
        int q = hash(key, i, table->capacity);
        if (table->buckets[q].slot == EMPTY || table->buckets[q].slot == DELETED) {
            table->buckets[q].key = key;
            table->buckets[q].value = value;
            table->buckets[q].slot = OCCPUIED;
            return;
        }
    }

    //means table is overflow
    resizeHashTable(table, table->capacity*2);
    hashtable_insert(table, key, value);
}
bool hashtable_find(HashTable* table, int key, int* outValue) {
    if (table == NULL) return false;

    int i=0;
    int q = hash(key, i, table->capacity);
    while (table->buckets[q].slot != EMPTY) {
        if (table->buckets[q].key = key) {
            *outValue = table->buckets[q].value;
            return true;
        }
        i++;
    }
    return false;
}
void hashtable_delete(HashTable* table, int key) {
    if (table == NULL) return;

    int i=0;
    int q = hash(key, i, table->capacity);
    while (table->buckets[q].slot != EMPTY) {
        if (table->buckets[q].key = key) {
            table->buckets[q].value = NULL;
            table->buckets[q].key = NULL;
            table->buckets[q].slot = DELETED;
            return;
        }
        i++;
    }
}

bool hashtable_contains(HashTable* table, int key) {
    int i=0;
    int q = hash(key, i, table->capacity);
    while (table->buckets[q].slot != EMPTY) {
        if (table->buckets[q].key = key) {
            return true;
        }
        i++;
    }
    return false;   
}  
void printHashTable(HashTable* table) {
    if (table == NULL) return;
    for (int i=0; i < table->capacity; i++)
        if (table->buckets[i].slot == OCCPUIED)
            printf("key:%d value:%d\n", table->buckets[i].key, table->buckets[i].value);   
}

int hashtable_size(HashTable* table) {
    if (table == NULL) return -1;
    int s = 0;
    for (int i=0; i < table->capacity; i++)
        if (table->buckets[i].slot == OCCPUIED)
            s++;   
    return s;
}
bool hashtable_isEmpty(HashTable* table) {return hashtable_size(table) == 0;}
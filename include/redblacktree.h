#include <stdbool.h>

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

typedef enum {RED, BLACK} NodeColor;

typedef struct RBNode {
    int key;
    int value;
    NodeColor color;
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* p;
} RBNode;

typedef struct RBTree{
    RBNode* root;
    RBNode* nil;
} RBTree;

void rb_init(RBTree* tree);
void rb_free(RBTree* tree);

void rb_insert(RBTree* tree, int key, int value);
void rb_remove(RBTree* tree, int key);

bool rb_contains(RBTree* tree, int key);
int rb_find(RBTree* tree, int key);

bool rb_isEmpty(RBTree* tree);

void rb_inorder(RBTree* tree, void (*visit)(int, int));
void rb_preorder(RBTree* tree, void (*visit)(int, int));
void rb_postorder(RBTree* tree, void (*visit)(int, int));

int rb_min(RBTree* tree);
int rb_max(RBTree* tree);

#endif
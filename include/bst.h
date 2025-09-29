#include <stdlib.h>
#include <stdbool.h>

#ifndef BST_H
#define BST_H

typedef struct BSTNode {
    int key;
    int value;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

typedef struct BSTree{
    BSTNode* root;
} BSTree;

void bst_init(BSTree* tree);
void bst_free(BSTree* tree);

void bst_insert(BSTree* tree, int key, int value);
void bst_remove(BSTree* tree, int key);

bool bst_contains(BSTree* tree, int key);
int bst_find(BSTree* tree, int key);

int bst_size(BSTree* tree);
bool bst_isEmpty(BSTree* tree);

void bst_inorder(BSTree* tree, void (*visit)(int, int));
void bst_preorder(BSTree* tree, void (*visit)(int, int));
void bst_postorder(BSTree* tree, void (*visit)(int, int));

int bst_min(BSTree* tree);
int bst_max(BSTree* tree);


#endif
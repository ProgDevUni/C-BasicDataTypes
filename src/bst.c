#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "bst.h"

static BSTNode* minNode(BSTNode* node) {
    if (node->left == NULL) return node;
    return minNode(node->left);
}

static BSTNode* maxNode(BSTNode* node) {
    if (node->right == NULL) return node;
    return maxNode(node->right);
}

void bst_init(BSTree* tree) {
    if (tree == NULL) return;
    tree->root = NULL;
}
static void freeNode(BSTNode* node) {
    if (node == NULL) return;
    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

void bst_free(BSTree* tree) {
    freeNode(tree->root);
    free(tree);
}

static BSTNode* insertNode(BSTNode* node, int key, int value) {
    if (node == NULL) {
        BSTNode* newNode = malloc(sizeof(BSTNode));
        newNode->key = key;
        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (node->key < key) {
        node->right = insertNode(node->right, key, value);
    }
    else if (node->key > key) {
        node->left = insertNode(node->left, key, value);
    }

    return node;
}

void bst_insert(BSTree* tree, int key, int value){
    tree->root = insertNode(tree->root, key, value);
}

static BSTNode* removeNode(BSTNode* node, int key) {
    if (node == NULL) return NULL;

    if (node->key < key) {
        node->right = removeNode(node->right, key);
    }
    else if (node->key > key) {
        node->left = removeNode(node->left, key);
    }
    else {
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        }
        else if (node->left == NULL) {
            BSTNode* temp = node->right;
            free(node);
            return temp;
        }
        else if (node->right == NULL) {
            BSTNode* temp = node->left;
            free(node);
            return temp;
        }
        else {
            BSTNode* temp = minNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = removeNode(node->right, temp->key);
        }
    }

    return node;
}

void bst_remove(BSTree* tree, int key){
    tree->root = removeNode(tree->root, key);
}

static BSTNode* findNode(BSTNode* node, int key) {
    if (node == NULL) return NULL;

    if (node->key < key) {
        return findNode(node->right, key);
    }
    else if (node->key > key) {
        return findNode(node->left, key);
    }
    else {
        return node;
    }
}
bool bst_contains(BSTree* tree, int key) {
    BSTNode* res = findNode(tree->root, key);
    return res != NULL;
}
int bst_find(BSTree* tree, int key) {
    return findNode(tree->root, key)->value;
}

static int sizeNode(BSTNode* node) {
    if (node == NULL) {return 0;}
    return 1 + sizeNode(node->left) + sizeNode(node->right);
}

int bst_size(BSTree* tree) {return sizeNode(tree->root);}
bool bst_isEmpty(BSTree* tree) {return tree->root == NULL;}

static void inorder(BSTNode* node, void (*visit)(int, int)) {
    if (node == NULL) return;
    inorder(node->left, visit);
    visit(node->key, node->value);
    inorder(node->right, visit);
}
void bst_inorder(BSTree* tree, void (*visit)(int, int)){
    if (tree == NULL || tree->root == NULL) return;
    inorder(tree->root, visit);
}

static void preorder(BSTNode* node, void (*visit)(int, int)) {
    if (node == NULL) return;
    visit(node->key, node->value);
    preorder(node->left, visit);
    preorder(node->right, visit);
}
void bst_preorder(BSTree* tree, void (*visit)(int, int)){
    if (tree == NULL || tree->root == NULL) return;
    preorder(tree->root, visit);
}

static void postorder(BSTNode* node, void (*visit)(int, int)) {
    if (node == NULL) return;
    postorder(node->left, visit);
    postorder(node->right, visit);
    visit(node->key, node->value);
}
void bst_postorder(BSTree* tree, void (*visit)(int, int)){
    if (tree == NULL || tree->root == NULL) return;
    postorder(tree->root, visit);
}

int bst_min(BSTree* tree) {
    return minNode(tree->root)->value;
}
int bst_max(BSTree* tree) {
    return maxNode(tree->root)->value;
}

/*
BSTree* tree;
    bst_init(tree);
    bst_insert(tree, 1, 10);
    bst_insert(tree, 9, 11);
    bst_insert(tree, 5, 12);
    bst_insert(tree, 11, 13);
    bst_insert(tree, 3, 14);
    bst_insert(tree, 4, 20);
    bst_insert(tree, 6, 22);

    bst_remove(tree, 5);
    bst_insert(tree, 7, 100);

    bst_remove(tree, 1);
    bst_remove(tree, 9);
    bst_remove(tree, 11);
    bst_remove(tree, 3);
    bst_remove(tree, 4);
    bst_remove(tree, 6);
    bst_remove(tree, 7);

    bst_inorder(tree, printNode);
    printf("=====\n");
    bst_preorder(tree, printNode);

    printf("\n%d\n", bst_isEmpty(tree));
*/

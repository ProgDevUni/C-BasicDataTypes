#include <stdlib.h>
#include <stdbool.h>

#include "redblacktree.h"

void rb_init(RBTree* tree){
    if (tree == NULL) return;

    tree->nil = (RBNode*) malloc(sizeof(RBNode));
    tree->nil->color = BLACK;
    tree->nil->left = tree->nil;
    tree->nil->right = tree->nil;
    tree->nil->p = tree->nil;

    tree->root = tree->nil;
}

static void freeNode(RBTree* tree,RBNode* node) {
    if (node == tree->nil) return;
    freeNode(tree, node->left);
    freeNode(tree, node->right);
    free(node);
}

void rb_free(RBTree* tree){
    freeNode(tree, tree->root);
}

static RBNode* minNode(RBTree* tree, RBNode* node) {
    if (node->left == tree->nil) return node;
    return minNode(tree, node->left);
}

static RBNode* maxNode(RBTree* tree, RBNode* node) {
    if (node->right == tree->nil) return node;
    return maxNode(tree, node->right);
}

static void left_rotate(RBTree* tree, RBNode* x) {
    RBNode* y = x->right;
    x->right = y->left;

    if (y->left != tree->nil)
        y->left->p = x;

    y->p = x->p;
    if (x->p == tree->nil)
        tree->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;

    y->left = x;
    x->p = y;
}

static void right_rotate(RBTree* tree, RBNode* x) {
    RBNode* y = x->left;
    x->left = y->right;

    if (y->right != tree->nil)
        y->right->p = x;
    
    y->p = x->p;

    if (x->p == tree->nil)
        tree->root = y;
    else if (x == x->p->left)
        x->p->left = y;
    else
        x->p->right = y;

    y->right = x;
    x->p = y;
}

static void insert_fixup(RBTree* tree, RBNode* z) {
    while (z->p->color == RED) {
        if (z->p == z->p->p->left) {
            RBNode* y = z->p->p->right;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z == z->p->right) {
                    z = z->p;
                    left_rotate(tree, z);
                }

                z->p->color = BLACK;
                z->p->p->color = RED;
                right_rotate(tree, z->p->p);
            }
        }
        else {
            RBNode* y = z->p->p->left;
            if (y->color == RED) {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else {
                if (z == z->p->left) {
                    z = z->p;
                    right_rotate(tree, z);
                }

                z->p->color = BLACK;
                z->p->p->color = RED;
                left_rotate(tree, z->p->p);
            }
        }
    }

    tree->root->color = BLACK;
}

void rb_insert(RBTree* tree, int key, int value){
    RBNode* z = (RBNode*) malloc(sizeof(RBNode));
    z->key = key;
    z->value = value;

    RBNode* x = tree->root;
    RBNode* y = tree->nil;

    while (x != tree->nil) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->p = y;

    if (y == tree->nil)
        tree->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    
    z->left = tree->nil;
    z->right = tree->nil;
    z->color = RED;
    insert_fixup(tree, z);
}

static void transplant(RBTree* tree, RBNode* u, RBNode* v) {
    if (u->p == tree->nil)
        tree->root = v;
    else if (u == u->p->left)
        u->p->left = v;
    else
        u->p->right = v;
    v->p = u->p;
}

static void remove_fixup(RBTree* tree, RBNode* x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->p->left) {
            RBNode* w = x->p->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                left_rotate(tree, x->p);
                w = x->p->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->p;
            }
            else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(tree, w);
                    w = x->p->right;
                }

                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                left_rotate(tree, x->p);
                x = tree->root;
            }
        }
        else {
            RBNode* w = x->p->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->p->color = RED;
                right_rotate(tree, x->p);
                w = x->p->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->p;
            }
            else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(tree, w);
                    w = x->p->left;
                }

                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                right_rotate(tree, x->p);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

static RBNode* findNode(RBTree* tree, RBNode* node, int key) {
    if (node == tree->nil) return NULL;

    if (node->key < key)
        return findNode(tree, node->right, key);
    else if (node->key > key)
        return findNode(tree, node->left, key);
    else
        return node;
}

void rb_remove(RBTree* tree, int key){
    RBNode* x;
    RBNode* z = findNode(tree, tree->root, key);
    RBNode* y = z;
    NodeColor y_original_color = y->color;

    if (z->left == tree->nil) {
        x = z->right;
        transplant(tree, z, z->right);
    }
    else if (z->right == tree->nil) {
        x = z->left;
        transplant(tree, z, z->left);
    }
    else {
        y = minNode(tree, z->right);
        y_original_color = y->color;
        x = y->right;
        if (y != z->right) {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->p = y;
        }
        else
            x->p = y;
        transplant(tree, z, y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK)
        remove_fixup(tree, x);
}

bool rb_contains(RBTree* tree, int key){
    return findNode(tree, tree->root, key) != NULL;
}
int rb_find(RBTree* tree, int key){
    return findNode(tree, tree->root, key)->value;
}

bool rb_isEmpty(RBTree* tree){return tree->root == tree->nil;}

static void inorder(RBTree* tree, RBNode* node, void (*visit)(int, int)) {
    if (node == tree->nil) return;
    inorder(tree, node->left, visit);
    visit(node->key, node->value);
    inorder(tree, node->right, visit);
}
void rb_inorder(RBTree* tree, void (*visit)(int, int)){
    if (tree == NULL || tree->root == tree->nil) return;
    inorder(tree, tree->root, visit);
}

static void preorder(RBTree* tree, RBNode* node, void (*visit)(int, int)) {
    if (node == tree->nil) return;
    visit(node->key, node->value);
    preorder(tree, node->left, visit);
    preorder(tree, node->right, visit);
}
void rb_preorder(RBTree* tree, void (*visit)(int, int)){
    if (tree == NULL || tree->root == tree->nil) return;
    preorder(tree, tree->root, visit);
}

static void postorder(RBTree* tree, RBNode* node, void (*visit)(int, int)) {
    if (node == tree->nil) return;
    postorder(tree, node->left, visit);
    postorder(tree, node->right, visit);
    visit(node->key, node->value);
}
void rb_postorder(RBTree* tree, void (*visit)(int, int)){
    if (tree == NULL || tree->root == tree->nil) return;
    postorder(tree, tree->root, visit);
}

int rb_min(RBTree* tree) {
    return minNode(tree, tree->root)->value;
}
int rb_max(RBTree* tree) {
    return maxNode(tree, tree->root)->value;
}
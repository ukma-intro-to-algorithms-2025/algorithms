#include "../include/node.h"
#include <stdlib.h>
#include <stdio.h>

NodePtr createNode(Key key, Value val) {
    NodePtr node = (NodePtr)malloc(sizeof(Node));
    if (node) {
        node->key = key;
        node->val = val;
        node->left = NULL;
        node->right = NULL;
        node->count = 1;
        node->color = RED;
    }
    return node;
}

void printNode(const NodePtr node) {
    if (node) {
        printf("Key: %s, Value: %s\n", (char*)node->key, (char*)node->val);
    }
}

NodePtr createRBNode(Key key, Value val, bool color) {
    NodePtr node = createNode(key, val);
    if (node) {
        node->color = color;
    }
    return node;
}

bool isRed(const NodePtr x) {
    if (x == NULL) return false;
    return x->color == RED;
}
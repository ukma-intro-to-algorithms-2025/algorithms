#include "../include/BST.h"
#include "../include/node.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Value BSTGet(NodePtr head, Key key) {
    NodePtr x = head;
    while (x != NULL) {
        if (less(key, x->key)) {
            x = x->left;
        } else if (greater(key, x->key)) {
            x = x->right;
        } else {
            return x->val;
        }
    }
    return NULL;
}

NodePtr BSTPut(NodePtr head, Key key, Value val) {
    if (head == NULL) {
        return createNode(key, val);  
    }
    if (less(key, head->key)) {
        head->left = BSTPut(head->left, key, val);
    } else if (greater(key, head->key)) {
        head->right = BSTPut(head->right, key, val);
    } else {
        head->val = val;
    }
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTFloor(NodePtr head, Key key) { //найближчий ключ  Floor(D) -> C      =<
    if (head == NULL) {
        return NULL;
    }
    
    if (equal(key, head->key)) {
        return head;
    }
    if (less(key, head->key)) {
        return BSTFloor(head->left, key);
    }
    NodePtr t = BSTFloor(head->right, key);
    return (t != NULL) ? t : head;
}

int BSTSize(NodePtr head) { //кількусть вузлів
     return (head != NULL) ? head->count : 0; }

void inorderNodes(NodePtr head, NodePtr *arr, int *index) { 
    if (head != NULL) {
        inorderNodes(head->left, arr, index);
        arr[(*index)++] = head; 
        inorderNodes(head->right, arr, index);
    }
}

NodePtr *BSTNodes(NodePtr head, int *arraySize) { //масив усіх вузлів у сорт порядку
    if (head == NULL) {
        *arraySize = 0;
        return NULL;
    }

    *arraySize = head->count;
    NodePtr *nodesArray = (NodePtr*)malloc((*arraySize) * sizeof(NodePtr));
    if (!nodesArray) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    int size = 0;
    inorderNodes(head, nodesArray, &size);
    return nodesArray;
}

NodePtr deleteMin(NodePtr head) { //*
    if (head->left == NULL) {
        NodePtr rightSubtree = head->right;
        free(head);         
        return rightSubtree; 
    }

    head->left = deleteMin(head->left);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTDeleteMin(NodePtr head) { //видалення мінімального 
    if (head == NULL)
        return NULL;
    
    return deleteMin(head);
}

NodePtr min(NodePtr head) { //найменший елемент
    while (head->left != NULL) {
        head = head->left;
    }
    return head;
}

NodePtr BSTDelete(NodePtr head, Key key) { //видалення елемента 
    if (head == NULL)
        return NULL;

    if (less(key, head->key)) {
        head->left = BSTDelete(head->left, key);
    } else if (greater(key, head->key)) {
        head->right = BSTDelete(head->right, key);
    } else {
        if (head->right == NULL) {
            NodePtr leftSubtree = head->left;
            free(head);
            return leftSubtree;
        }
        if (head->left == NULL) {
            NodePtr rightSubtree = head->right;
            free(head);
            return rightSubtree;
        }

        NodePtr temp = min(head->right);
        head->key = temp->key;
        head->val = temp->val;
        head->right = deleteMin(head->right);
    }

    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

void BSTDestroy(NodePtr head) { 
    if (head == NULL)
        return;

    BSTDestroy(head->left);  
    BSTDestroy(head->right);  
    free(head);  
}

void BSTIterate(NodePtr head, void (*func)(NodePtr)) { //виведення елементів у сорт порядку
    if (head == NULL)
        return;

    BSTIterate(head->left, func);
    func(head);
    BSTIterate(head->right, func);
}

//new function hm6

NodePtr BSTCeiling(NodePtr head, Key key) { //найближчий ключ Ceiling(D) -> E   >=
    if (head == NULL) {
        return NULL;
    }
    if (equal(key, head->key)) {
        return head;
    }
    if (greater(key, head->key)) {
        return BSTCeiling(head->right, key);
    }
    NodePtr t = BSTCeiling(head->left, key);
    return (t != NULL) ? t : head;
}

int BSTRank(NodePtr head, Key key) { //кількість ключів, менших за заданий 
    if (head == NULL) {
        return 0;
    }
    if (less(key, head->key)) {
        return BSTRank(head->left, key);
    } else if (greater(key, head->key)) {
        return 1 + BSTSize(head->left) + BSTRank(head->right, key);
    } else {
        return BSTSize(head->left);
    }
}

NodePtr BSTSelect(NodePtr head, int k) { //k найменший елемент
    if (head == NULL) {
        return NULL;
    }
    
    int leftSize = BSTSize(head->left);
    
    if (k < leftSize) {
        return BSTSelect(head->left, k);
    } else if (k > leftSize) {
        return BSTSelect(head->right, k - leftSize - 1);
    } else {
        return head;
    }
}
 
Key BSTMin(NodePtr head) { //найменший ключ
    if (head == NULL) {
        return NULL;
    }
    while (head->left != NULL) {
        head = head->left;
    }
    return head->key;
}
 
Key BSTMax(NodePtr head) { //найбільший ключ
    if (head == NULL) {
        return NULL;
    }
    while (head->right != NULL) {
        head = head->right;
    }
    return head->key;
}
 
NodePtr BSTDeleteMax(NodePtr head) { //видалення найбільшого елемента
    if (head == NULL) {
        return NULL;
    }
    if (head->right == NULL) {
        NodePtr leftSubtree = head->left;
        free(head);
        return leftSubtree;
    }
    head->right = BSTDeleteMax(head->right);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}
 
void BSTPrint(const NodePtr head) { //вивід елементів у сорт. порядку (зростання)
    if (head == NULL) {
        return;
    }
    BSTPrint(head->left);
    printf("%s ", head->key);
    BSTPrint(head->right);
}
 
void BSTPrintReverse(const NodePtr head) { //вивід елементів у зворотньому  (спадання)
    if (head == NULL) {
        return;
    }
    BSTPrintReverse(head->right);
    printf("%s ", head->key);
    BSTPrintReverse(head->left);
}

int isBSTUtil(NodePtr head, Key minKey, Key maxKey) {
    if (head == NULL) {
        return 1;  
    }
    if (minKey != NULL && less(head->key, minKey)) {
        return 0;  
    }
    if (maxKey != NULL && greater(head->key, maxKey)) {
        return 0; 
    }
    return isBSTUtil(head->left, minKey, head->key) &&
           isBSTUtil(head->right, head->key, maxKey);
}

int isBST(NodePtr head) {
    return isBSTUtil(head, NULL, NULL);
}
#include "../include/BST.h"
#include "../include/node.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

NodePtr BSTFloor(NodePtr head, Key key) {
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

NodePtr BSTCeiling(NodePtr head, Key key) {
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

int BSTRank(NodePtr head, Key key) {
    if (head == NULL) return 0;
    
    if (less(key, head->key)) {
        return BSTRank(head->left, key);
    } else if (greater(key, head->key)) {
        return 1 + BSTSize(head->left) + BSTRank(head->right, key);
    } else {
        return BSTSize(head->left);
    }
}

int BSTSize(NodePtr head) { 
    return (head != NULL) ? head->count : 0; 
}

void inorderNodes(NodePtr head, NodePtr *arr, int *index) {
    if (head != NULL) {
        inorderNodes(head->left, arr, index);
        arr[(*index)++] = head;
        inorderNodes(head->right, arr, index);
    }
}

NodePtr *BSTNodes(NodePtr head, int *arraySize) {
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

NodePtr deleteMin(NodePtr head) {
    if (head->left == NULL) {
        NodePtr rightSubtree = head->right;
        free(head);
        return rightSubtree;
    }

    head->left = deleteMin(head->left);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTDeleteMin(NodePtr head) {
    if (head == NULL)
        return NULL;
    
    return deleteMin(head);
}

NodePtr deleteMax(NodePtr head) {
    if (head->right == NULL) {
        NodePtr leftSubtree = head->left;
        free(head);
        return leftSubtree;
    }

    head->right = deleteMax(head->right);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTDeleteMax(NodePtr head) {
    if (head == NULL)
        return NULL;
    
    return deleteMax(head);
}

NodePtr min(NodePtr head) {
    while (head->left != NULL) {
        head = head->left;
    }
    return head;
}

NodePtr max(NodePtr head) {
    while (head->right != NULL) {
        head = head->right;
    }
    return head;
}

Key BSTMin(NodePtr head) {
    if (head == NULL) return NULL;
    NodePtr x = min(head);
    return x->key;
}

Key BSTMax(NodePtr head) {
    if (head == NULL) return NULL;
    NodePtr x = max(head);
    return x->key;
}

NodePtr BSTDelete(NodePtr head, Key key) {
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

void BSTIterate(NodePtr head, void (*func)(NodePtr)) {
    if (head == NULL)
        return;

    BSTIterate(head->left, func);
    func(head);
    BSTIterate(head->right, func);
}

void BSTPrint(NodePtr head) {
    if (head == NULL) return;
    BSTPrint(head->left);
    printf("%s(%s) ", head->key, head->color == RED ? "R" : "B");
    BSTPrint(head->right);
}

int calculateHeight(NodePtr node) {
    if (node == NULL) return 0;
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}


NodePtr createMinHeightBST(Key arr[], int start, int end) {
    if (start > end) {
        return NULL;
    }
    
    int mid = (start + end) / 2;
    
    NodePtr root = createNode(arr[mid], arr[mid]);
    
    root->left = createMinHeightBST(arr, start, mid - 1);
    root->right = createMinHeightBST(arr, mid + 1, end);

    root->count = 1 + BSTSize(root->left) + BSTSize(root->right);
    
    return root;
}

int isBalancedOptimized(NodePtr node, int *height) {
    if (node == NULL) {
        *height = 0;
        return 1;
    }
    
    int leftHeight = 0, rightHeight = 0;
    
    if (!isBalancedOptimized(node->left, &leftHeight)) {
        return 0;
    }
    
    if (!isBalancedOptimized(node->right, &rightHeight)) {
        return 0;
    }
    
    *height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    
    return abs(leftHeight - rightHeight) <= 1;
}

int isBalanced(NodePtr node) {
    int height = 0;
    return isBalancedOptimized(node, &height);
}

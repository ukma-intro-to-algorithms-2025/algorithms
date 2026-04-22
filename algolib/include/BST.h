#ifndef BST_H
#define BST_H

#include "node.h"

typedef Node* NodePtr;

// Basic operations
NodePtr BSTPut(NodePtr, Key key, Value val);
Value BSTGet(NodePtr, Key key);

// Search operations
NodePtr BSTFloor(NodePtr, Key key);
NodePtr BSTCeiling(NodePtr, Key key);

// Order statistics
int BSTRank(NodePtr, Key key);
NodePtr BSTSelect(NodePtr root, int k);

// Tree information
int BSTSize(NodePtr);

// Collection operations
NodePtr *BSTNodes(NodePtr head, int *arraySize);
void BSTIterate(NodePtr head, void (*func)(NodePtr));

// Delete operations
NodePtr BSTDeleteMin(NodePtr root);
NodePtr BSTDelete(NodePtr, Key key);
NodePtr BSTDeleteMax(NodePtr root);

// Min and Max
Key BSTMin(NodePtr);
Key BSTMax(NodePtr);

// Print operations
void BSTPrint(const NodePtr);
void BSTPrintReverse(const NodePtr);

// Validation
int isBST(NodePtr head);

// Cleanup
void BSTDestroy(NodePtr);

#endif
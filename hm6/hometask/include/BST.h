#ifndef BST_H
#define BST_H

#include "node.h"

typedef Node* NodePtr;

NodePtr BSTPut(NodePtr, Key key, Value val);
Value BSTGet(NodePtr, Key key);

NodePtr BSTFloor(NodePtr, Key key);
NodePtr BSTCeiling(NodePtr, Key key);

int BSTRank(NodePtr, Key key);
NodePtr BSTSelect(NodePtr root, int k);

int BSTSize(NodePtr);

NodePtr *BSTNodes(NodePtr head, int *arraySize);
void BSTIterate(NodePtr head, void (*func)(NodePtr));

NodePtr BSTDeleteMin(NodePtr root);
NodePtr BSTDelete(NodePtr, Key key);
NodePtr BSTDeleteMax(NodePtr root);

Key BSTMin(NodePtr);
Key BSTMax(NodePtr);

void BSTPrint(const NodePtr);
void BSTPrintReverse(const NodePtr);

// Validation
int isBST(NodePtr head);

// Cleanup
void BSTDestroy(NodePtr);

#endif

#ifndef BST_H
#define BST_H

#include "node.h"

NodePtr BSTPut(NodePtr, Key key, Value val);
Value BSTGet(NodePtr, Key key);
NodePtr BSTFloor(NodePtr, Key key);
NodePtr BSTCeiling(NodePtr, Key key);
int BSTRank(NodePtr, Key key);
int BSTSize(NodePtr);
NodePtr *BSTNodes(NodePtr head, int *arraySize);
void BSTIterate(NodePtr head, void (*func)(NodePtr));
NodePtr BSTDeleteMin(NodePtr root);
NodePtr BSTDelete(NodePtr, Key key);
Key BSTMin(NodePtr);
Key BSTMax(NodePtr);
NodePtr BSTDeleteMax(NodePtr root);
void BSTPrint(NodePtr head);
void BSTDestroy(NodePtr);

NodePtr createMinHeightBST(Key arr[], int start, int end);

int calculateHeight(NodePtr node);
int isBalanced(NodePtr node); 
int isBalancedOptimized(NodePtr node, int *height);

#endif
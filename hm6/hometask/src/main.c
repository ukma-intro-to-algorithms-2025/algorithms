#include "../include/BST.h"
#include <stdio.h>
#include <stdlib.h>

void print_node(NodePtr node) {
    if (node) {
        printf("%s ", node->key);
    }
}

int main() {
    printf("\n BST Demonstration \n\n");
    
    NodePtr head = create_node("S", NULL);
    BSTPut(head, "E", NULL);
    BSTPut(head, "X", NULL);
    BSTPut(head, "A", NULL);
    BSTPut(head, "R", NULL);
    BSTPut(head, "C", NULL);
    BSTPut(head, "H", NULL);
    
    printf("Tree (in-order): ");
    BSTIterate(head, print_node);
    printf("\n");
    
    printf("Tree (reverse): ");
    BSTPrintReverse(head);
    printf("\n");
    
    printf("\nMin key: %s\n", BSTMin(head));
    printf("Max key: %s\n", BSTMax(head));
    
    printf("\nRank of 'R': %d\n", BSTRank(head, "R"));
    printf("3rd smallest element: %s\n", BSTSelect(head, 3)->key);
    printf("Ceiling of 'G': %s\n", BSTCeiling(head, "G")->key);
    printf("Floor of 'G': %s\n", BSTFloor(head, "G")->key);
    
    printf("\nIs BST? %s\n", isBST(head) ? "YES" : "NO");
    
    BSTDestroy(head);
    
    return 0;
}
#include "../include/LLRB.h"
#include "../include/BST.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void test_LLRBPut(void);
void test_LLRBBalance(void);
void testMinHeightBST(void);
int test_LLRBProperties(NodePtr head);

void test_LLRBPut() {
    NodePtr head = NULL;

    char keys[][2] = {"M", "J", "R", "E", "L", "P", "X", "C", "H", "S", "A"};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < num_keys; i++) {
        head = LLRBPut(head, keys[i], keys[i]);
    }

    printf("Printing BST:\n");
    BSTPrint(head);
    printf("\n");

    assert(equal(head->key, "M"));
    assert(equal(head->left->key, "J"));
    assert(equal(head->right->key, "R"));
    assert(equal(head->left->left->key, "E"));
    assert(equal(head->left->right->key, "L"));
    assert(equal(head->right->left->key, "P"));
    assert(equal(head->right->right->key, "X"));
    assert(equal(head->left->left->left->key, "C"));
    assert(equal(head->left->left->right->key, "H"));
    assert(equal(head->right->right->left->key, "S"));
    assert(equal(head->left->left->left->left->key, "A"));

    assert(!isRed(head));           // M - black
    assert(!isRed(head->left));     // J - black
    assert(!isRed(head->right));    // R - black
    assert(isRed(head->left->left)); // E - red
    assert(!isRed(head->left->right)); // L - black
    assert(!isRed(head->right->left)); // P - black
    assert(!isRed(head->right->right)); // X - black
    assert(!isRed(head->left->left->left)); // C - black
    assert(!isRed(head->left->left->right)); // H - black
    assert(isRed(head->right->right->left)); // S - red
    assert(isRed(head->left->left->left->left)); // A - red

    BSTDestroy(head);
    printf("test_LLRBPut passed.\n");
}

int test_LLRBProperties(NodePtr head) {
    if (head == NULL) return 1;
    
    if (isRed(head->left) && isRed(head->right)) {
        printf("Property 1 violated: Node %s has two red children\n", head->key);
        return 0;
    }
    
    if (isRed(head->right)) {
        printf("Property 2 violated: Node %s has a red right link\n", head->key);
        return 0;
    }

    return test_LLRBProperties(head->left) && test_LLRBProperties(head->right);
}

void test_LLRBBalance(void) {
    NodePtr bst_head = NULL;
    NodePtr llrb_head = NULL;
    
    printf("\nAscending order insertion (A to K) \n");
    
    char *keys[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K"};
    int num_keys = sizeof(keys) / sizeof(keys[0]);
    
    for (int i = 0; i < num_keys; i++) {
        bst_head = BSTPut(bst_head, keys[i], keys[i]);
        llrb_head = LLRBPut(llrb_head, keys[i], keys[i]);
    }
    
    printf("BST height: %d\n", calculateHeight(bst_head));
    printf("LLRB height: %d\n", calculateHeight(llrb_head));
    printf("LLRB is balanced: %s\n", isBalanced(llrb_head) ? "Yes" : "No");
    printf("LLRB properties: %s\n", test_LLRBProperties(llrb_head) ? "OK" : "FAILED");
    
    BSTDestroy(bst_head);
    BSTDestroy(llrb_head);
    
    printf("\nDescending order insertion (K to A)\n");
    bst_head = NULL;
    llrb_head = NULL;
    
    for (int i = num_keys - 1; i >= 0; i--) {
        bst_head = BSTPut(bst_head, keys[i], keys[i]);
        llrb_head = LLRBPut(llrb_head, keys[i], keys[i]);
    }
    
    printf("BST height: %d\n", calculateHeight(bst_head));
    printf("LLRB height: %d\n", calculateHeight(llrb_head));
    printf("LLRB is balanced: %s\n", isBalanced(llrb_head) ? "Yes" : "No");
    printf("LLRB properties: %s\n", test_LLRBProperties(llrb_head) ? "OK" : "FAILED");
    
    BSTDestroy(bst_head);
    BSTDestroy(llrb_head);
}

void testMinHeightBST(void) {
    printf("\nMin Height BST from Sorted Array\n");
    
    Key sorted_arr[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K"};
    int n = sizeof(sorted_arr) / sizeof(sorted_arr[0]);
    
    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%s ", sorted_arr[i]);
    }
    printf("\n");
    
    NodePtr root = createMinHeightBST(sorted_arr, 0, n - 1);
    
    printf("\nMin height BST (in-order traversal):\n");
    BSTPrint(root);
    printf("\n");
    
    printf("\nTree height: %d\n", calculateHeight(root));
    printf("Tree is balanced: %s\n", isBalanced(root) ? "Yes" : "No");
    
    printf("\nTree structure (root is '%s'):\n", root->key);
    printf("  Left subtree root: %s\n", root->left ? root->left->key : "NULL");
    printf("  Right subtree root: %s\n", root->right ? root->right->key : "NULL");
    
    BSTDestroy(root);
}

int main() {
    printf(" Test LLRB\n");
    printf("LLRB Properties\n\n");
    test_LLRBPut();
    
    printf("\nLLRB Properties Check\n");
    NodePtr head = NULL;
    char keys[][2] = {"M", "J", "R", "E", "L", "P", "X", "C", "H", "S", "A"};
    int num_keys = sizeof(keys) / sizeof(keys[0]);
    
    for (int i = 0; i < num_keys; i++) {
        head = LLRBPut(head, keys[i], keys[i]);
    }
    
    printf("LLRB properties: %s\n", test_LLRBProperties(head) ? "PASSED" : "FAILED");
    printf("Tree height: %d\n", calculateHeight(head));
    printf("Tree is balanced: %s\n", isBalanced(head) ? "Yes" : "No");
    BSTDestroy(head);
    
    test_LLRBBalance();
    
    testMinHeightBST();
    
    printf(" Test LLRB completed\n");

    return 0;
}
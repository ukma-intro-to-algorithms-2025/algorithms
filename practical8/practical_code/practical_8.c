#include "BST.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_BSTFloor() {
    printf("\n Testing BSTFloor n");
    
    {
        NodePtr head = NULL;
        assert(BSTFloor(head, "A") == NULL);
        printf("Test 1 (empty tree) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("M", NULL);
        assert(equal(BSTFloor(head, "M")->key, "M"));
        assert(BSTFloor(head, "N") == NULL);
        assert(BSTFloor(head, "L") == NULL);
        printf("Test 2 (one element) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("M", NULL);
        BSTPut(head, "C", NULL);
        assert(equal(BSTFloor(head, "C")->key, "C"));
        assert(equal(BSTFloor(head, "D")->key, "C"));
        assert(equal(BSTFloor(head, "M")->key, "M"));
        printf("Test 3 (one left element) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("M", NULL);
        BSTPut(head, "Z", NULL);
        assert(equal(BSTFloor(head, "Z")->key, "Z"));
        assert(equal(BSTFloor(head, "Y")->key, "M"));
        assert(equal(BSTFloor(head, "M")->key, "M"));
        printf("Test 4 (one right element) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "A", NULL);
        
        assert(equal(BSTFloor(head, "A")->key, "A"));
        assert(equal(BSTFloor(head, "B")->key, "B"));
        assert(equal(BSTFloor(head, "C")->key, "C"));
        assert(equal(BSTFloor(head, "D")->key, "D"));
        assert(equal(BSTFloor(head, "E")->key, "D"));
        printf("Test 5 (multiple left elements) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("A", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "D", NULL);
        
        assert(equal(BSTFloor(head, "A")->key, "A"));
        assert(equal(BSTFloor(head, "B")->key, "B"));
        assert(equal(BSTFloor(head, "C")->key, "C"));
        assert(equal(BSTFloor(head, "D")->key, "D"));
        assert(BSTFloor(head, "Z") == NULL);
        printf("Test 6 (multiple right elements) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("M", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "Z", NULL);
        
        assert(equal(BSTFloor(head, "A")->key, "C"));
        assert(equal(BSTFloor(head, "C")->key, "C"));
        assert(equal(BSTFloor(head, "M")->key, "M"));
        assert(equal(BSTFloor(head, "Y")->key, "M"));
        assert(equal(BSTFloor(head, "Z")->key, "Z"));
        printf("Test 7 (one left and one right) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("A", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "D", NULL);
        BSTPut(head, "E", NULL);
        
        assert(equal(BSTFloor(head, "D")->key, "D"));
        assert(equal(BSTFloor(head, "C")->key, "C"));
        assert(equal(BSTFloor(head, "F")->key, "E"));
        printf("Test 8 (multiple right moves) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("E", NULL);
        BSTPut(head, "D", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "A", NULL);
        
        assert(equal(BSTFloor(head, "B")->key, "B"));
        assert(equal(BSTFloor(head, "C")->key, "C"));
        assert(equal(BSTFloor(head, "A")->key, "A"));
        assert(BSTFloor(head, "Z") == NULL);
        printf("Test 9 (multiple left moves) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);
        BSTPut(head, "M", NULL);
        
        assert(equal(BSTFloor(head, "Q")->key, "M"));
        assert(equal(BSTFloor(head, "H")->key, "H"));
        assert(equal(BSTFloor(head, "K")->key, "H"));
        assert(equal(BSTFloor(head, "Y")->key, "X"));
        assert(equal(BSTFloor(head, "S")->key, "S"));
        assert(equal(BSTFloor(head, "B")->key, "A"));
        printf("Test 10 (mixed moves) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("M", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "X", NULL);
        
        assert(BSTFloor(head, "A") == NULL);
        printf("Test 11 (key smaller than all) passed.\n");
        BSTDestroy(head);
    }
    
    printf("\nAll BSTFloor tests passed!\n");
}

void test_BSTCeiling() {
    printf("\nTesting BSTCeiling \n");
    
    {
        NodePtr head = NULL;
        assert(BSTCeiling(head, "A") == NULL);
        printf("Test 1 (empty tree) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("M", NULL);
        assert(equal(BSTCeiling(head, "M")->key, "M"));
        assert(equal(BSTCeiling(head, "L")->key, "M"));
        assert(BSTCeiling(head, "N") == NULL);
        printf("Test 2 (single element) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);
        
        assert(equal(BSTCeiling(head, "Q")->key, "R"));
        assert(equal(BSTCeiling(head, "H")->key, "H"));
        assert(equal(BSTCeiling(head, "K")->key, "R"));
        assert(BSTCeiling(head, "Y") == NULL);
        printf("Test 3 (complex tree) passed.\n");
        BSTDestroy(head);
    }
    
    printf("\nAll BSTCeiling tests passed!\n");
}

void test_BSTRank() {
    printf("\nTesting BSTRank\n");
    
    {
        NodePtr head = NULL;
        assert(BSTRank(head, "A") == 0);
        printf("Test 1 (empty tree) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("M", NULL);
        assert(BSTRank(head, "M") == 0);
        assert(BSTRank(head, "N") == 1);
        assert(BSTRank(head, "L") == 0);
        printf("Test 2 (single element) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);
        
        assert(BSTRank(head, "A") == 0);
        assert(BSTRank(head, "C") == 1);
        assert(BSTRank(head, "E") == 2);
        assert(BSTRank(head, "H") == 3);
        assert(BSTRank(head, "R") == 4);
        assert(BSTRank(head, "S") == 5);
        assert(BSTRank(head, "X") == 6);
        assert(BSTRank(head, "Z") == 7);
        printf("Test 3 (complex tree) passed.\n");
        BSTDestroy(head);
    }
    
    printf("\nAll BSTRank tests passed!\n");
}

void test_BSTMinMax() {
    printf("\n Testing BSTMin and BSTMax \n");
    
    {
        NodePtr head = NULL;
        assert(BSTMin(head) == NULL);
        assert(BSTMax(head) == NULL);
        printf("Test 1 (empty tree) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("M", NULL);
        assert(equal(BSTMin(head), "M"));
        assert(equal(BSTMax(head), "M"));
        printf("Test 2 (single element) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);
        
        assert(equal(BSTMin(head), "A"));
        assert(equal(BSTMax(head), "X"));
        printf("Test 3 (complex tree) passed.\n");
        BSTDestroy(head);
    }
    
    printf("\nAll BSTMin and BSTMax tests passed!\n");
}

void test_BSTDeleteMin() {
    printf("\n Testing BSTDeleteMin\n");
    
    {
        NodePtr head = NULL;
        assert(BSTDeleteMin(head) == NULL);
        printf("Test 1 (empty tree) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("D", NULL);
        NodePtr new_head = BSTDeleteMin(head);
        assert(new_head == NULL);
        printf("Test 2 (single node) passed.\n");
        BSTDestroy(new_head);
    }
    {
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(new_head == head);
        assert(BSTSize(new_head) == 2);
        printf("Test 3 (left-skewed tree) passed.\n");
        BSTDestroy(new_head);
    }
    {
        NodePtr head = create_node("A", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "C", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(equal(new_head->key, "B"));
        assert(BSTSize(new_head) == 2);
        assert(equal(new_head->right->key, "C"));
        assert(new_head->left == NULL);
        printf("Test 4 (root is min) passed.\n");
        BSTDestroy(new_head);
    }
    {
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "F", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(equal(new_head->key, "D"));
        assert(BSTSize(new_head) == 3);
        assert(equal(new_head->left->key, "C"));
        assert(equal(new_head->right->key, "F"));
        printf("Test 5 (tree with both subtrees) passed.\n");
        BSTDestroy(new_head);
    }
    {
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "F", NULL);

        NodePtr new_head = BSTDeleteMin(head);
        assert(equal(new_head->key, "D"));
        assert(BSTSize(new_head) == 3);
        assert(equal(new_head->left->key, "C"));
        assert(equal(new_head->right->key, "F"));
        printf("Test 6 (balanced tree) passed.\n");
        BSTDestroy(new_head);
    }

    printf("\nAll BSTDeleteMin tests passed!\n");
}

void test_BSTDeleteMax() {
    printf("\n Testing BSTDeleteMax \n");
    
    {
        NodePtr head = NULL;
        assert(BSTDeleteMax(head) == NULL);
        printf("Test 1 (empty tree) passed.\n");
        BSTDestroy(head);
    }
    {
        NodePtr head = create_node("M", NULL);
        NodePtr new_head = BSTDeleteMax(head);
        assert(new_head == NULL);
        printf("Test 2 (single element) passed.\n");
        BSTDestroy(new_head);
    }
    {
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "A", NULL);
        
        int old_size = BSTSize(head);
        NodePtr new_head = BSTDeleteMax(head);
        assert(BSTSize(new_head) == old_size - 1);
        assert(equal(new_head->key, "D"));
        printf("Test 3 (left-skewed tree) passed.\n");
        BSTDestroy(new_head);
    }
    {
        NodePtr head = create_node("A", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "D", NULL);
        
        NodePtr new_head = BSTDeleteMax(head);
        assert(equal(new_head->key, "A"));
        assert(BSTSize(new_head) == 3);
        printf("Test 4 (right-skewed tree) passed.\n");
        BSTDestroy(new_head);
    }
    {
        NodePtr head = create_node("S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);
        
        int old_size = BSTSize(head);
        NodePtr new_head = BSTDeleteMax(head);
        assert(BSTSize(new_head) == old_size - 1);
        assert(equal(BSTMax(new_head), "S"));
        printf("Test 5 (complex tree) passed.\n");
        BSTDestroy(new_head);
    }
    
    printf("\nAll BSTDeleteMax tests passed!\n");
}

int main() {
    test_BSTFloor();
    test_BSTCeiling();
    test_BSTRank();
    test_BSTMinMax();
    test_BSTDeleteMin();
    test_BSTDeleteMax();
    printf("All tests passed successfully!\n");

    return 0;
}

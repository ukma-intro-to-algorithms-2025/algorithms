#include "../include/BST.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void print_node(NodePtr node) {
    if (node) {
        printf("%s ", node->key);
    }
} 

void test_BSTCeiling() {
    printf("\n Testing BSTCeiling \n");
     
    {
        NodePtr head = NULL;
        assert(BSTCeiling(head, "A") == NULL);
        printf("++ Empty tree\n");
        BSTDestroy(head);
    }
    
    {
        NodePtr head = create_node("M", NULL);
        assert(equal(BSTCeiling(head, "M")->key, "M"));
        assert(equal(BSTCeiling(head, "L")->key, "M"));
        assert(BSTCeiling(head, "N") == NULL);
        BSTDestroy(head);
        printf("++  Single element\n");
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
        assert(equal(BSTCeiling(head, "A")->key, "A"));
        BSTDestroy(head);
        printf("++ Complex tree\n");
    }
    
    printf("All BSTCeiling tests passed\n");
}
void test_BSTRank() {
    printf("\n Testing BSTRank \n");
     
    {
        NodePtr head = NULL;
        assert(BSTRank(head, "A") == 0);
        printf("++ Empty tree\n");
        BSTDestroy(head);
    }
     
    {
        NodePtr head = create_node("M", NULL);
        assert(BSTRank(head, "M") == 0);
        assert(BSTRank(head, "N") == 1);
        assert(BSTRank(head, "L") == 0);
        BSTDestroy(head);
        printf("++ Single element\n");
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
        BSTDestroy(head);
        printf("++ Complex tree\n");
    }
    
    printf("All BSTRank tests passed\n");
}

void test_BSTSelect() {
    printf("\n Testing BSTSelect \n");
     
    {
        NodePtr head = NULL;
        assert(BSTSelect(head, 0) == NULL);
        printf("++ Empty tree\n");
        BSTDestroy(head);
    }
     
    {
        NodePtr head = create_node("M", NULL);
        assert(equal(BSTSelect(head, 0)->key, "M"));
        assert(BSTSelect(head, 1) == NULL);
        BSTDestroy(head);
        printf("++ Single element\n");
    }
     
    {
        NodePtr head = create_node("S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);
         
        assert(equal(BSTSelect(head, 0)->key, "A"));
        assert(equal(BSTSelect(head, 1)->key, "C"));
        assert(equal(BSTSelect(head, 2)->key, "E"));
        assert(equal(BSTSelect(head, 3)->key, "H"));
        assert(equal(BSTSelect(head, 4)->key, "R"));
        assert(equal(BSTSelect(head, 5)->key, "S"));
        assert(equal(BSTSelect(head, 6)->key, "X"));
        assert(BSTSelect(head, 7) == NULL);
        BSTDestroy(head);
        printf("++ Complex tree\n");
    }
    
    printf("All BSTSelect tests passed\n");
}
 
void test_BSTMinMax() {
    printf("\nTesting BSTMin and BSTMax \n");
     
    {
        NodePtr head = NULL;
        assert(BSTMin(head) == NULL);
        assert(BSTMax(head) == NULL);
        printf("++ Empty tree\n");
        BSTDestroy(head);
    }
     
    {
        NodePtr head = create_node("M", NULL);
        assert(equal(BSTMin(head), "M"));
        assert(equal(BSTMax(head), "M"));
        BSTDestroy(head);
        printf("++ Single element\n");
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
        BSTDestroy(head);
        printf("++ Complex tree\n");
    }
    
    printf("All BSTMin and BSTMax tests passed\n");
}

void test_BSTDeleteMax() {
    printf("\nTesting BSTDeleteMax \n");
    
    {
        NodePtr head = NULL;
        assert(BSTDeleteMax(head) == NULL);
        printf("++ Empty tree\n");
        BSTDestroy(head);
    }

    {
        NodePtr head = create_node("M", NULL);
        NodePtr new_head = BSTDeleteMax(head);
        assert(new_head == NULL);
        printf("++ Single element\n");
        BSTDestroy(new_head);
    }
    
    {
        NodePtr head = create_node("A", NULL);
        BSTPut(head, "B", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "D", NULL);
        
        NodePtr new_head = BSTDeleteMax(head);
        assert(equal(BSTMax(new_head), "C"));
        assert(BSTSize(new_head) == 3);
        BSTDestroy(new_head);
        printf("++ Right-skewed tree\n");
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
        BSTDestroy(new_head);
        printf("++ Complex tree\n");
    }
    
    printf("All BSTDeleteMax tests passed\n");
}
void test_BSTPrintReverse() {
    printf("\n Testing BSTPrintReverse\n");
     
    {
        NodePtr head = NULL;
        BSTPrintReverse(head);
        printf("++ Empty tree (no output)\n");
        BSTDestroy(head);
    }
     
    {
        NodePtr head = create_node("M", NULL);
        printf("Expected: M\nGot: ");
        BSTPrintReverse(head);
        printf("\n");
        BSTDestroy(head);
        printf("++ Single element\n");
    }
    
    {
        NodePtr head = create_node("S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);
        
        printf("Expected: X S R H E C A\nGot: ");
        BSTPrintReverse(head);
        printf("\n");
        BSTDestroy(head);
        printf("++ Complex tree\n");
    }
    
    printf("All BSTPrintReverse tests passed\n");
}

void test_isBST() {
    printf("\nTesting isBST\n");
    
    {
        NodePtr head = NULL;
        assert(isBST(head) == 1);
        printf("++ Empty tree is BST\n");
        BSTDestroy(head);
    }

    {
        NodePtr head = create_node("M", NULL);
        assert(isBST(head) == 1);
        BSTDestroy(head);
        printf("++ Single node is BST\n");
    }
    
    {
        NodePtr head = create_node("S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);
        
        assert(isBST(head) == 1);
        BSTDestroy(head);
        printf("++ Valid BST\n");
    }
    
    {
        NodePtr head = create_node("M", NULL);
        NodePtr left = create_node("N", NULL);
        head->left = left;
        head->right = NULL;
        
        assert(isBST(head) == 0);
        free(left);
        free(head);
        printf("Invalid BST (left child > root)\n");
    }
    
    {
        NodePtr head = create_node("M", NULL);
        NodePtr right = create_node("L", NULL);
        head->right = right;
        head->left = NULL;
        
        assert(isBST(head) == 0);
        free(right);
        free(head);
        printf("Invalid BST (right child < root)\n");
    }
    
    printf("All isBST tests passed\n");
}

void test_BSTFloor() {
    printf("\nTesting BSTFloor\n");
    
    {
        NodePtr head = NULL;
        assert(BSTFloor(head, "A") == NULL);
        printf("++ Empty tree\n");
        BSTDestroy(head);
    }
    
    {
        NodePtr head = create_node("M", NULL);
        assert(equal(BSTFloor(head, "M")->key, "M"));
        assert(equal(BSTFloor(head, "N")->key, "M"));
        assert(BSTFloor(head, "L") == NULL);
        BSTDestroy(head);
        printf("++ Single element\n");
    }
    
    {
        NodePtr head = create_node("S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);
        
        assert(equal(BSTFloor(head, "Q")->key, "H"));
        assert(equal(BSTFloor(head, "H")->key, "H"));
        assert(equal(BSTFloor(head, "K")->key, "H"));
        assert(equal(BSTFloor(head, "Y")->key, "X"));
        assert(equal(BSTFloor(head, "A")->key, "A"));
        BSTDestroy(head);
        printf("++ Complex tree\n");
    }
    
    printf("All BSTFloor tests passed\n");
}

void test_BSTDeleteMin() {
    printf("\nTesting BSTDeleteMin\n");
    
    {
        NodePtr head = NULL;
        assert(BSTDeleteMin(head) == NULL);
        printf("++ Empty tree\n");
        BSTDestroy(head);
    }
    
    {
        NodePtr head = create_node("M", NULL);
        NodePtr new_head = BSTDeleteMin(head);
        assert(new_head == NULL);
        printf("++ Single element\n");
        BSTDestroy(new_head);
    }
    
    {
        NodePtr head = create_node("D", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "B", NULL);
        
        NodePtr new_head = BSTDeleteMin(head);
        assert(equal(BSTMin(new_head), "C"));
        assert(BSTSize(new_head) == 2);
        BSTDestroy(new_head);
        printf("++ Left-skewed tree\n");
    }
    
    {
        NodePtr head = create_node("S", NULL);
        BSTPut(head, "E", NULL);
        BSTPut(head, "X", NULL);
        BSTPut(head, "A", NULL);
        BSTPut(head, "R", NULL);
        BSTPut(head, "C", NULL);
        BSTPut(head, "H", NULL);
        
        NodePtr new_head = BSTDeleteMin(head);
        assert(equal(BSTMin(new_head), "C"));
        assert(BSTSize(new_head) == 6);
        BSTDestroy(new_head);
        printf("++ Complex tree\n");
    }
    
    printf("All BSTDeleteMin tests passed\n");
}

int main() {
    printf("BST - Tests\n");
    test_BSTCeiling();     
    test_BSTRank();        
    test_BSTSelect();    
    test_BSTMinMax();     
    test_BSTDeleteMax();   
    test_BSTPrintReverse(); 
    test_isBST();
    test_BSTFloor();
    test_BSTDeleteMin();
    printf("All tests passed\n");
    
    return 0;
}
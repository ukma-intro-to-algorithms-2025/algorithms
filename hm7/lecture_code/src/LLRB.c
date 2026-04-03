#include "../include/LLRB.h"
#include "../include/item.h"
#include "../include/LLRB_ops.h"
#include <assert.h>

NodePtr llrb_put_impl(NodePtr head, Key key, Value val) {
    if (head == NULL) {
        return createRBNode(key, val, RED); 
    }

    if (less(key, head->key)) {
        head->left = llrb_put_impl(head->left, key, val);
    } else if (greater(key, head->key)) {
        head->right = llrb_put_impl(head->right, key, val);
    } else {
        head->val = val; 
    }

    if (isRed(head->right) && !isRed(head->left)) {
        head = rotateLeft(head);
    }

    if (isRed(head->left) && isRed(head->left->left)) {
        head = rotateRight(head);
    }

    if (isRed(head->left) && isRed(head->right)) {
        flipColors(head);
    }

    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    assert(!isRed(head->right));

    return head;
}

NodePtr LLRBPut(NodePtr head, Key key, Value val) {
    NodePtr new_head = llrb_put_impl(head, key, val);
    if (new_head != NULL) {
        new_head->color = BLACK;
    }
    return new_head;
}

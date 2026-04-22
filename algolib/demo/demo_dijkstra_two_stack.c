#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/stack.h"

int main() {
    char expression[] = "( 1 + ( ( 2 + 3 ) * ( 4 * 5 ) ) )";
    printf("Expression: %s\n", expression);
    
    StackPtr vals = StackInit();
    StackPtr ops = StackInit();
    
    char* token = strtok(expression, " ");
    while (token != NULL) {
        if (strcmp(token, "(") == 0) {
        } else if (strcmp(token, "+") == 0) {
            push(ops, token);
        } else if (strcmp(token, "-") == 0) {
            push(ops, token);
        } else if (strcmp(token, "*") == 0) {
            push(ops, token);
        } else if (strcmp(token, "/") == 0) {
            push(ops, token);
        } else if (strcmp(token, ")") == 0) {
            char* op = pop(ops);
            double v = *(double*)pop(vals);
            
            if (strcmp(op, "+") == 0)
                v = *(double*)pop(vals) + v;
            else if (strcmp(op, "-") == 0)
                v = *(double*)pop(vals) - v;
            else if (strcmp(op, "*") == 0)
                v = *(double*)pop(vals) * v;
            else if (strcmp(op, "/") == 0)
                v = *(double*)pop(vals) / v;
            
            double* result = malloc(sizeof(double));
            *result = v;
            push(vals, result);
        } else {
            double* val = malloc(sizeof(double));
            *val = atof(token);
            push(vals, val);
        }
        token = strtok(NULL, " ");
    }
    
    double result = *(double*)pop(vals);
    printf("Result: %.0f\n", result);
    
    StackDestroy(vals);
    StackDestroy(ops);
    return 0;
}
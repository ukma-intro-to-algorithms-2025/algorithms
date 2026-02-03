#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

void evaluate(StackPtr ops, StackPtr vals) {
    char *op = pop(ops);
    double *v2 = pop(vals);
    double *v1 = pop(vals);
    double *res = malloc(sizeof(double));
    if (*op == '+') *res = *v1 + *v2;
    else if (*op == '-') *res = *v1 - *v2;
    else if (*op == '*') *res = *v1 * *v2;
    else if (*op == '/') *res = *v1 / *v2;
    push(vals, res);
    free(op); free(v1); free(v2);
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    FILE *file = fopen(argv[1], "r");
    if (!file) return 1;
    StackPtr ops = StackInit(), vals = StackInit();
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c) || c == '(') continue;
        else if (isdigit(c)) {
            ungetc(c, file);
            double *val = malloc(sizeof(double));
            if (fscanf(file, "%lf", val) != 1) { free(val); continue; }
            push(vals, val);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            char *op = malloc(sizeof(char));
            *op = (char)c;
            push(ops, op);
        } else if (c == ')') {
            if (!StackEmpty(ops)) evaluate(ops, vals);
        }
    }
    while (!StackEmpty(ops)) evaluate(ops, vals);
    double *finalRes = pop(vals);
    if (finalRes) { printf("Result: %.2f\n", *finalRes); free(finalRes); }
    StackDestroy(ops); StackDestroy(vals);
    fclose(file);
    return 0;
}
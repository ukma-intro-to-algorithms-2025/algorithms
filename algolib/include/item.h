#ifndef ITEM_H
#define ITEM_H

#include <string.h>

typedef char* Key;

static inline int less(Key a, Key b) {
    if (a == NULL || b == NULL) return 0;
    return strcmp(a, b) < 0;
}

static inline int greater(Key a, Key b) {
    if (a == NULL || b == NULL) return 0;
    return strcmp(a, b) > 0;
}

static inline int equal(Key a, Key b) {
    if (a == NULL || b == NULL) return (a == b);
    return strcmp(a, b) == 0;
}

#endif
#ifndef KMP_H
#define KMP_H

#include <stddef.h>

void kmp_build_lps(const char *pattern, int m, int *lps);

int *kmp_search(const char *text, const char *pattern, int *count);

#endif 

#include "../include/kmp.h"
#include <stdlib.h>
#include <string.h>

void kmp_build_lps(const char *pattern,int m,int *lps) {
    lps[0]=0;
    int len=0;
    int i=1;
    while (i<m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i]=len;
            i++;
        } else {
            if (len!=0) {
                len=lps[len- 1];
            } else {
                lps[i]=0;
                i++;
            }
        }
    }
}
int *kmp_search(const char *text,const char *pattern,int *count) {
    int n=(int)strlen(text);
    int m=(int)strlen(pattern);
    *count=0;

    if (m==0 || n==0 || m>n) return NULL;
    int *lps=(int*)malloc(m*sizeof(int));
    if (!lps) return NULL;

    kmp_build_lps(pattern,m,lps);
    int capacity=16;
    int *results=(int*)malloc(capacity*sizeof(int));
    if (!results) { free(lps); return NULL; }
    int i=0;
    int j=0; 

    while (i<n) {
        if (text[i]==pattern[j]) {
            i++;
            j++;
        }
        if (j==m) {
            if (*count==capacity) {
                capacity*=2;
                int *tmp=(int*)realloc(results,capacity*sizeof(int));
                if(!tmp) { free(results); free(lps); return NULL; }
                results=tmp;
            }
            results[(*count)++]=i-j;
            j= lps[j-1];
        } else if (i<n &&text[i] != pattern[j]) {
            if (j!= 0)
                j=lps[j-1];
            else
                i++;
        }
    }
    free(lps);
    if (*count==0) {
        free(results);
        return NULL;
    }
    return results;
}

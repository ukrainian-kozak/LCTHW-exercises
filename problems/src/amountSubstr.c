#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static inline void preKmp(char* string, int m, int len, int *pi)
{
    pi[0] = 0;

    for (int i = 1; i < len; ++i) {
        int j = pi[i-1];
        while (j > 0 && string[i] != string[j])
            j = pi[j-1];
        if (string[i] == string[j])
            ++j;
        pi[i] = j;
    }
}

int find(char *text, char *pattern)
{
    if (strcmp(text,"") == 0 && strcmp(pattern, "") == 0)
        return 1;
    if (text == NULL || pattern == NULL)
        return 0;
    if (strcmp(text,"") == 0 || strcmp(pattern, "") == 0)
        return 0;


    int plen = strlen(pattern);
    int tlen = strlen(text);
    char *result = (char*)malloc((plen + tlen + 2) * sizeof(char));
    
    int i = 0;
    for (i = 0; i < plen; ++i) {
        result[i] = pattern[i];
    }
    result[i++] = '#';
    for (int j = 0; j < tlen; ++j) {
        result[i++] = text[j];
    }
    result[i] = '\0';

    int rlen = strlen(result);
    int* pi = (int*)malloc(rlen * sizeof(int));
    preKmp(result, plen, rlen, pi);

    int ans = 0;
    int j = 0;
    for (int i = plen + 1; i < rlen; ++i) {
        
        while (j > 0 && result[j] != result[i]) {
            j = pi[j-1];
        }  
        if (result[i] == result[j])
            ++j;
        if (j == plen) {
            ++ans;
            j = 0;
        }
    }

    if (result)
        free(result);

    return ans;
}


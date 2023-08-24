#include <lcthw/algorithm.h>
#include <stdlib.h>
#include <lcthw/dbg.h>
int Max(const int a, const int b)
{
    return a > b ? a : b;
}

/*BM*/
static inline void preBmBc(bstring pattern, int m, int bmBc[]) 
{
    int i = 0;

    for ( ; i < ASIZE; ++i)
        bmBc[i] = m;
    for (i = 0; i < m - 1; ++i)
        bmBc[bchar(pattern, i)] = m - i - 1;
}
/*BM*/
ssize_t BM(bstring pattern, bstring string)
{
    int plen = blength(pattern);
    int slen = blength(string);
    int j, i, bmBc[ASIZE];
    /*CPP*/
    preBmBc(pattern, plen, bmBc);

    /*Searching*/
    i = plen - 1;
    j = i;
    while (j < slen) {
        if (bchar(pattern, i) == bchar(string, j)) {
            if (i == 0)
                return j;

            --i;
            --j;
        } else {
            j += bmBc[bchar(string, j)];
            i = plen - 1;
        }        
    }

    return -1;
}


/*KMP*/
static inline void cppKMP(bstring pattern, int m, int *pi)
{
    pi[0] = 0;
    int j = 0;

    for (int i = 1; i < m; ++i) {
        while (j > 0 && bchar(pattern, i) != bchar(pattern, j)) {
            j = pi[j-1];
        }
        if (bchar(pattern, i) == bchar(pattern, j)) {
            ++j;
        }
        pi[i] = j;
    }
}

/*KMP*/
ssize_t KMP(bstring pattern, bstring text)
{
    int n = blength(text);
    int m = blength(pattern);
    int *pi = (int *) malloc(m * sizeof(int));
    check(pi != NULL, "Memory allocated error");

    /*CPP*/
    cppKMP(pattern, m, pi);

    for (int i = 1, j = 0; i < n; ++i) {
        while (j > 0 && bchar(text, i) != bchar(pattern, j)) {
            j = pi[j-1];
        }
        if (bchar(text, i) == bchar(pattern, j)) {
            ++j;
        }
        if (j == m) {
            free(pi);
            return i - m + 1;
        }
    }

    free(pi);
    return -1;

error:
    return -1;
}





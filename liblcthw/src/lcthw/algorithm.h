#ifndef algorithm_h
#define algorithm_h

#include <stdio.h>
#include <sys/types.h>
#include <lcthw/bstrlib.h>
#include <lcthw/dbg.h>

#define OUTPUT(A) printf("Match found at position: %d\n", A)

#define ASIZE 256

ssize_t BM(bstring pattern, bstring string);

ssize_t KMP(bstring pattern, bstring text);

#endif

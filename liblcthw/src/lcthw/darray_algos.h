#ifndef darray_algos_h
#define darray_algos_h

#include <lcthw/darray.h>

typedef int (*DArray_compare) (const void*, const void*);

int DArray_qsort(DArray * array, DArray_compare cmp);

//int DArray_heapsort(DArray * array, DArray_compare cmp);

//int DArray_mergesort(DArray * array, DArray_compare cmp);

#endif

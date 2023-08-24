#include <lcthw/darray_algos.h>
#include <stdlib.h>

int DArray_qsort(DArray * array, DArray_compare cmp)
{
    qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
    return 0;
}

//static inline void Swap(int* a, int* b)
//{
//    int temp = *a;
//    *a = *b;
//    *b = temp;
//}
//
//static void heapify(DArray * array, const int size, const int index)
//{
//    int largest = index;
//    int left = index * 2 + 1;
//    int right = index * 2 + 2;
//    
//    if (left < size && DArray_get(array, left) > DArray_get(array, largest))
//        largest = left;
//    if (right < size && DArray_get(array, right) > DArray_get(array, largest))
//        largest = right;
//    
//    if (largest != index) {
//        Swap(DArray_get(array, largest), DArray_get(array, index));
//        heapify(array, size, largest);
//    }
//}
//
//static void heapsort(DArray * array, const int size) 
//{
//    for (int i = size / 2 - 1; i >= 0; --i) {
//        heapify(array, size, i);
//    }
//
//    for (int i = size - 1; i >= 0; --i) {
//        Swap(DArray_get(array, 0), DArray_get(array, i));
//
//        heapify(array, i, 0);
//    }
//}
//
//int DArray_heapsort(DArray * array, DArray_compare cmp)
//{
//    
//}
//
//int DArray_mergesort(DArray * array, DArray_compare cmp)
//{
//    mergesort(array->contents, DArray_count(array),
//            sizeof(void*), cmp);
//    return 0;
//}

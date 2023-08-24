#ifndef LCTHW_LIST_ALGOS_H
#define LCTHW_LIST_ALGOS_H

#include <lcthw/list.h>
#include <stdio.h>

typedef int (*List_compare) (const void *, const void *);
int mycmp(const void* a, const void* b);

void List_print(List * list);

int List_bubble_sort(List * list, List_compare cmp);

List* List_merge_sort(List * list, List_compare cmp);

List* List_bottom_up_merge_sort(List * list, List_compare cmp);

#endif


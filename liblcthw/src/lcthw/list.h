#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

struct ListNode;
struct List;

typedef struct ListNode {
    void *value;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode;

typedef struct List {
    int count;
    ListNode *head;
    ListNode *tail;
} List;

List *List_create();
List *List_copy(List * list);

void List_destroy(List * list);
void List_clear(List * list);
void List_clear_destroy(List * list);

#define List_count(A) ((A)->count)
#define List_head(A) ((A)->head != NULL ? (A)->head->value : NULL)
#define List_tail(A) ((A)->tail != NULL ? (A)->tail->value : NULL)

void List_push(List * list, void *value);
void *List_pop(List * list);
void List_unshift(List * list, void *value);
void *List_shift(List * list);

void *List_remove(List * list, ListNode * node);

void List_concat(List* list1, List* list2);

#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
                                                   ListNode *V = NULL;\
for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif

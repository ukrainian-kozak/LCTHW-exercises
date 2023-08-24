#include <lcthw/list_algos.h>

int mycmp(const void* a, const void* b)
{
    if (*(int*)a < *(int*)b) return -1;
    if (*(int*)a == *(int*)b) return 0;
    return 1;
}

void List_print(List * list)
{
    LIST_FOREACH(list, head, next, curr) {
        printf("%p ", curr->value);
    }

    printf("\n");
}

inline void ListNode_swap(ListNode *a, ListNode *b)
{
    void *temp = a->value;
    a->value = b->value;
    b->value = temp;
}

int List_bubble_sort(List * list, List_compare cmp)
{
    int sorted = 0;

    if (List_count(list) <= 1)
        return 0;
    

    while (!sorted) {
        sorted = 1;
        LIST_FOREACH(list, head, next, curr) {
            if (curr->next) {
                if (cmp(curr->value, curr->next->value) > 0) {
                    ListNode_swap(curr, curr->next);
                    sorted = 0;
                }
            }
        }
    }

    return 0;
}

List *List_merge(List * left, List * right, List_compare cmp)
{
    List *result = List_create();
    void *val = NULL;


    while (List_count(left) > 0 || List_count(right) > 0) {
        if (List_count(left) > 0 && List_count(right) > 0) {
            if (cmp(List_head(left), List_head(right)) <= 0) {
                val = List_shift(left);
            } else {
                val = List_shift(right);
            }

            List_push(result, val);
        } else if (List_count(left) > 0) {
            val = List_shift(left);
            List_push(result, val);
        } else {
            val = List_shift(right);
            List_push(result, val);
        }
    }


    return result;
}

List* List_merge_sort(List * list, List_compare cmp) 
{
    if (List_count(list) <= 1)
        return list;

    List* left = List_create();
    List* right = List_create();
    int middle = List_count(list) / 2;

    LIST_FOREACH(list, head, next, curr) {
        if (middle > 0) {
            List_push(left, curr->value);
        } else {
            List_push(right, curr->value);
        }
        --middle;
    }

    left  = List_merge_sort(left, cmp);
    right = List_merge_sort(right, cmp);

    return List_merge(left, right, cmp);
}

List* List_bottom_up_merge_sort(List * list, List_compare cmp)
{
    if (List_count(list) <= 1)
        return list;

    List* sorted_lists[List_count(list)];
    int i = 0;

    LIST_FOREACH(list, head, next, curr) {
        List* sub_list = List_create();
        List_push(sub_list, curr->value);
        sorted_lists[i++] = sub_list;
    }

    int num_lists = List_count(list);
    while (num_lists > 1) {
        i = 0;
        for (int j = 0; j < num_lists; j += 2) {
            if (j == num_lists - 1) {
                sorted_lists[i++] = sorted_lists[j];
            } else {
                sorted_lists[i++] = List_merge(sorted_lists[j], sorted_lists[j + 1], cmp);
            }
        }
        num_lists = i;
    }

    List* sorted_list = sorted_lists[0];

    for (i = 0; i < num_lists; ++i) {
        if (sorted_lists[i] != sorted_list) {
            List_clear_destroy(sorted_lists[i]);
        }
    }

    return sorted_list;
}



























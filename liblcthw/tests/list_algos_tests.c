#include "minunit.h"
#include <assert.h>
#include <string.h>
#include <lcthw/list_algos.h>

char *values[] = {"XXXX", "1234", "abcd", "xjvef", "NDSS"};

#define NUM_VALUES 5

List *create_words()
{
    int i = 0;
    List *words = List_create();

    for (i = 0; i < NUM_VALUES; ++i) {
        List_push(words, values[i]);
    }

    return words;
}

int is_sorted(List * list)
{
    LIST_FOREACH(list, head, next, curr) {
        if (curr->next && strcmp(curr->value, curr->next->value) > 0) {
            debug("%s %s", (char*)curr->value, (char*)curr->value);
            return 0;
        }
    }

    return 1;
}



char *test_bubble_sort()
{
    List *words = create_words();

    List_print(words);

    int rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sort is failed.");
    mu_assert(is_sorted(words), "Is_sorted failed.");

    rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sorte is failed.");
    mu_assert(is_sorted(words), "Is_sorted failed on a sorted list.");

    List_destroy(words);
    words = List_create();

    rc = List_bubble_sort(words, (List_compare) strcmp);
    mu_assert(rc == 0, "Bubble sorte is failed on empty list.");
    mu_assert(is_sorted(words), "Is_sorted failed on empty list.");

    List_destroy(words);

    return NULL;
}

char *test_merge_sort()
{
    List *words = create_words();

    List *res = List_merge_sort(words, (List_compare) strcmp);
    mu_assert(is_sorted(res), "Merge sort failed.");

    List *res2 = List_merge_sort(res, (List_compare) strcmp);
    mu_assert(is_sorted(res2), "Merge sort failed.");

    List_destroy(res2);
    List_destroy(res);
    List_destroy(words);

    return NULL;
}

char* bottom_up_merge_sort()
{
    List* words = create_words();

    List *res = List_bottom_up_merge_sort(words, (List_compare) strcmp);
    mu_assert(is_sorted(res), "Bottom up failed.");

    List *res2 = List_bottom_up_merge_sort(res, (List_compare) strcmp);
    mu_assert(is_sorted(res2), "Bottom up2 failed.");

    List_destroy(res2);
    List_destroy(res);
    List_destroy(words);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);
    mu_run_test(bottom_up_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);

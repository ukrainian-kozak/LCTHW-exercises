#include "minunit.h"
#include <lcthw/list.h>
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";

char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}

char *test_destroy()
{
    List_clear_destroy(list);

    return NULL;
}

char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_tail(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_tail(list) == test2, "Wrong last value.");

    List_push(list, test3);
    mu_assert(List_tail(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_copy()
{
    List_push(list, test1);
    mu_assert(List_tail(list) == test1, "Wrong push.");
    List_push(list, test2);
    mu_assert(List_tail(list) == test2, "Wrong push.");
    List_push(list, test3);
    mu_assert(List_tail(list) == test3, "Wrong push.");
    mu_assert(List_count(list) == 3, "Wrong count after push.");

    List* copy = List_copy(list);
    ListNode* node = copy->head;
    LIST_FOREACH(list, head, next, curr) {
        mu_assert(node->value == curr->value, "Wrong copy.");
        node = node->next;
    }

    char* val = List_pop(copy);
    mu_assert(val == test3, "Wrong on pop copy.");

    val = List_pop(copy);
    mu_assert(val == test2, "Wrong on pop copy.");

    val = List_pop(copy);
    mu_assert(val == test1, "Wrong on pop copy.");
    mu_assert(List_count(copy) == 0, "Wrong count after pop copy.");

    for (int i = 0; i < 3; ++i) {
        (void)List_pop(list);
    }

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_head(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_head(list) == test2, "Wrong first value.");

    List_unshift(list, test3);
    mu_assert(List_head(list) == test3, "Wrong first value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    char *val = List_remove(list, list->head->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_head(list) == test3, "Wrong first value after remove.");
    mu_assert(List_tail(list) == test1, "Wrong last value after remove.");

    return NULL;
}

char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong value after shift.");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_copy);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);

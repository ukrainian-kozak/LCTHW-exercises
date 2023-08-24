#include "minunit.h"
#include <lcthw/list_algos.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdio.h>


char *unsorted_values[] = { "XXXX", "1234", "abcd", "xjvef", "NDSS" };
#define SIZE 5
#define REPEAT 100000

void create_words(List * list)
{
    if (list == NULL)
        List_create(list);

    for (int i = 0; i < SIZE; ++i) {
        List_push(list, unsorted_values[i]);
    }
}


void fill_list(List * list)
{
    for (int i = 0; i < REPEAT; ++i) {
        List* concat = List_create();
        create_words(concat);
        List_concat(list, concat);
    }
}

char* bubble_sort_time()
{
    List* list1 = List_create();
    fill_list(list1);
    clock_t start = clock();
    List_bubble_sort(list1, (List_compare) strcmp);
    clock_t end = clock();
    double total = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Bubble sort: %f\n", total);

    List_destroy(list1);

    return NULL;
}

char* merge_sort_time()
{
    List* list2 = List_create();
    fill_list(list2);
    clock_t start = clock();
    List_merge_sort(list2, (List_compare) strcmp);
    clock_t end = clock();
    double total = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Merge sort: %f\n", total);

    List_destroy(list2);

    return NULL;
}

char* bottom_up_merge_sort_time()
{
    List* list3 = List_create();
    fill_list(list3);
    clock_t start = clock();
    List_bottom_up_merge_sort(list3, (List_compare) strcmp);
    clock_t end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Bottom up merge sort: %f\n", time);

    List_destroy(list3);

    return NULL;
}

char* all_tests()
{
    mu_suite_start();

    //mu_run_test(bubble_sort_time);
    mu_run_test(merge_sort_time);
    mu_run_test(bottom_up_merge_sort_time);

    return NULL;
}

RUN_TESTS(all_tests);









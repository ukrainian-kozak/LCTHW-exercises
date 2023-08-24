#include "minunit.h"
#include <lcthw/darray.h>
#include <lcthw/list.h>
#include <time.h>

char *value = "Value ";

#define SIZE_1 100
#define SIZE_2 1000
#define SIZE_3 10000
#define SIZE_4 100000
#define SIZE_5 1000000



char* test_speed(int size)
{
    printf("%d elements:\n\n", size);

    printf("Push:\n");

    List* list = List_create();
    
    clock_t start = clock();

    for (int i = 0; i < size; ++i) {
        List_push(list, value);
    }

    clock_t end = clock();
    double total = (double)(end - start) / CLOCKS_PER_SEC;

    printf("List: %f\n", total);

    DArray* array = DArray_create(sizeof(char*), 1);
    start = clock();
    
    for (int i = 0; i < size; ++i) {
        value = DArray_new(array);
        DArray_push(array, value);
    }

    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;

    printf("DArray: %f\n\n", total);
    printf("Pop:\n");

    start = clock();
    List_destroy(list);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;

    printf("List: %f\n", total);

    start = clock();
    DArray_clear_destroy(array);
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;

    printf("DArray: %f\n", total);

    return NULL;
}  

char* test_all_sizes()
{
    test_speed(SIZE_1);
    test_speed(SIZE_2);
    test_speed(SIZE_3);
    test_speed(SIZE_4);
    test_speed(SIZE_5);

    return NULL;
}

char* all_tests()
{
    mu_suite_start();

    mu_run_test(test_all_sizes);

    return NULL;
}

RUN_TESTS(all_tests);

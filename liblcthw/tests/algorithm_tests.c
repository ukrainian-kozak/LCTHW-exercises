#include "minunit.h"
#include <lcthw/bstrlib.h>
#include <lcthw/algorithm.h>
#include <lcthw/darray.h>
#include <time.h>

struct tagbstring text = bsStatic("I have ALPHA and ALPHA");
struct tagbstring pattern = bsStatic("ALPHA");

struct tagbstring alphabet = bsStatic("qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890");

#define SIZE 10000000

//static inline void fiil_array(DArray * array)
//{
//    for (int i = 0; i < SIZE; ++i) {
//        DArray_new(array);
//        DArray_push(array, alphabet);
//    }
//}

static inline int get_rand(const int a, const int b)
{
    srand(time(NULL));

    return a + rand() % (b - a + 1);
}

static inline void fill_targets(DArray * array)
{
int len = blength(&alphabet);

    for (int i = 0; i < SIZE; ++i) {
        DArray_new(array);

        int start = get_rand(0, len - 1);
        int end = get_rand(0, len - start + 1);
        
        bstring substring = bmidstr(&alphabet, start, end);
        DArray_push(array, substring);
    } 
}

char* test_bm_and_kmp()
{
    int rc = BM(&pattern, &text);
    mu_assert(rc != -1, "BM failed");

    int rc2 = KMP(&pattern, &text);
    mu_assert(rc2 != -1, "KMP failed");
    mu_assert(rc == rc2, "KMP or BM is wrong implemented");

    return NULL;
}

char* test_bm_speed()
{
    //DArray *array = DArray_create();
    DArray *to_find = DArray_create(SIZE, sizeof(bstring));

    //fill_array(array);
    fill_targets(to_find);

    time_t start = clock();

    for (int i = 0; i < DArray_count(to_find); ++i) {
        BM(DArray_get(to_find, i), &alphabet);
    }

    time_t end = clock();
    double total = (double)(end - start) / CLOCKS_PER_SEC;

    fprintf(stderr, "BM for 100 strings in avrg: %f", total);
    
    DArray_destroy(to_find);

    return NULL;
}

char* test_kmp_speed()
{
    DArray *to_find = DArray_create(SIZE, sizeof(bstring));

    fill_targets(to_find);

    time_t start = clock();

    for (int i = 0; i < DArray_count(to_find); ++i) {
        KMP(DArray_get(to_find, i), &alphabet);
    }

    time_t end = clock();
    double total = (double)(end - start) / CLOCKS_PER_SEC;

    fprintf(stderr, "KMP for 100 strings in avrg: %f", total);
    
    DArray_destroy(to_find);

    return NULL;
}

char* all_tests()
{
    mu_suite_start();

    mu_run_test(test_bm_and_kmp);
#if 1
    mu_run_test(test_bm_speed);
    mu_run_test(test_kmp_speed);

 #endif

    return NULL;
}

RUN_TESTS(all_tests);

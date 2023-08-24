#include "unit.h"
#include <amountSubstr.c>

char *test_problem()
{
    char *str = "";
    char *to_find = "";
    int check = find(str, to_find);
    mu_assert(check == 1, "Wrong case 1");

    str = "abc";
    to_find = "ab";
    check = find(str, to_find);
    mu_assert(check == 1, "Wrong case 2");

    str = "";
    to_find = "aa";
    check = find(str, to_find);
    mu_assert(check == 0, "Wrong case 3");
    
    str = "aaaa";
    to_find = "aa";
    check = find(str, to_find);
    mu_assert(check > 0, "Wrong case 4");
    
    str = "qwertre";
    to_find = "";
    check = find(str, to_find);
    mu_assert(check == 0, "Wrong case 5");
    
    str = "avbfgeeew";
    to_find = "geeew";
    check = find(str, to_find);
    mu_assert(check == 1, "Wrong case 6");

    str = "Seva Top 1";
    to_find = "eva ";
    check = find(str, to_find);
    mu_assert(check == 1, "Wrong case 7");

    str = "vitalyk";
    to_find = "vitalyk";
    check = find(str, to_find);
    mu_assert(check == 1, "Wrong case 8");
   
    str = "VvVvvV";
    to_find = "Vv";
    check = find(str, to_find);
    mu_assert(check == 2, "Wrong case 9");
    
    str = "Anton";
    to_find = "Gandon";
    check = find(str, to_find);
    mu_assert(check == 0, "Wrong case 10");

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_problem);

    return NULL;
}

RUN_TESTS(all_tests);





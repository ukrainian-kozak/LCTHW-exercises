#include "minunit.h"
#include <lcthw/bstrlib.h>
#include <assert.h>
#include <stdio.h>


char* test_bfromcstr()
{
    bstring bstr = bfromcstr("abcd");
    mu_assert(bstr != NULL, "Wrong bfromcstr.");
    bdestroy(bstr);

    return NULL;
}

char* test_blk2bstr()
{
    bstring bstr = blk2bstr("abcdfghj", 4);
    mu_assert(bstr != NULL, "Wrong blk2bstr.");

    return NULL;
}

char* test_cpy_assign()
{
    bstring bstr = bfromcstr("string");
    bstring cbstr = bstrcpy(bstr);
    printf("%s\n", (char*)bstr->data);
    printf("%s\n", (char*)cbstr->data);

    mu_assert(cbstr != NULL, "Wrong bstrcpy.");
    mu_assert(biseq(bstr, cbstr), "Wrong copy.");
    
    bstring abstr = bfromcstr("");
    int rc = bassign(abstr, cbstr);
    printf("%s\n", (char*)abstr->data);

    mu_assert(rc == BSTR_OK, "Wrong assign.");
    mu_assert(biseq(abstr, cbstr), "Wrong assign.");

    rc = bassigncstr(abstr, "abcd"); 
    printf("%s\n", (char*)abstr->data);

    mu_assert(rc == BSTR_OK, "Wrong assigncstr.");
    mu_assert(biseq(bfromcstr("abcd"), abstr), "Wrong assigncstr.");

    rc = bassignblk(bstr, "abcd", 4);
    mu_assert(rc == BSTR_OK, "Wrong bassignblk.");
    mu_assert(biseq(bstr, abstr), "Wrong bassignblk.");

    bstring con = bfromcstr("");
    rc = bconcat(con, bstr);
    mu_assert(rc == BSTR_OK, "Wrong concat.");
    mu_assert(biseq(con, bstr), "Wrong concat");

    bdestroy(con);
    bdestroy(abstr);
    bdestroy(cbstr);
    bdestroy(bstr);
return NULL;
}

char* test_find()
{
    bstring bstr = bfromcstr("abcd");
    int rc = binstr(bstr, 0, bfromcstr("ab"));

    mu_assert(rc == 0, "Wrong find");
    


}

char* all_tests()
{
    mu_suite_start();

    mu_run_test(test_bfromcstr);
    mu_run_test(test_blk2bstr);
    mu_run_test(test_cpy_assign);

    return NULL;
}

RUN_TESTS(all_tests);

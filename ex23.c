#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include <time.h>

typedef int(*DuffDevice)(char*, char*, int);

int normal_copy(char *from, char *to, int count)
{
    int i = 0;

    for (i = 0; i < count; ++i) {
        to[i] = from[i];
    }

    return i;
}


int duffs_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;

        switch (count % 8) {
            case 0:
                do {
                    *to++ = *from++;
                    case 7:
                     *to++ = *from++;
                    case 6:
                     *to++ = *from++;
                    case 5:
                     *to++ = *from++;
                    case 4:
                     *to++ = *from++;
                    case 3:
                     *to++ = *from++;
                    case 2:
                     *to++ = *from++;
                    case 1:
                     *to++ = *from++;
                } while (--n > 0);
        }
    }

    return count;
}

int zeds_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;

        switch (count % 8) {
            case 0:
again:      *to++ = *from++;
            printf("%c", *to);
            case 7:
            *to++ = *from++;
            printf("%c", *to);
            case 6:
            *to++ = *from++;
            printf("%c", *to);
            case 5:
            *to++ = *from++;
            printf("%c", *to);
            case 4:
            *to++ = *from++;
            printf("%c", *to);
            case 3:
            *to++ = *from++;
            printf("%c", *to);
            case 2:
            *to++ = *from++;
            printf("%c", *to);
            case 1:
            *to++ = *from++;
            printf("%c", *to);
            if (--n > 0)
                goto again;
        }
    }

    return count;
}

int valid_copy(char *data, int count, char expects)
{
    int i = 0;
    for (i = 0; i < count; ++i) {
        if (data[i] != expects) {
            log_err("[%d] %c != %c", i, data[i], expects);
            return 0;
        }
    }

    return 1;
}

double testPerfomance(char *from, char *to, int count,
        int(*duffs)(char*, char*, int)) 
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    duffs(from, to, count);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

int main(int argc, char *argv[]) 
{
    int count = 1000000;
    char from[1000000] = { 'a' };
    char to[1000000] = { 'c' };
    int rc = 0;
    //set up the from to have some stuff
    memset(from, 'x', count);
    //set it to a failure mode
    memset(to, 'y', count);
    check(valid_copy(to, count, 'y'), "Not initialized right.");

    //use normal copy to
    rc = normal_copy(from, to, count);
    check(rc == count, "Normal copy failed: %d", rc);
    check(valid_copy(to, count, 'x'), "Normal copy failed.");

    //reset
    memset(to, 'y', count);

    //duffs version
    rc = duffs_device(from, to, count);
    check(rc == count, "Duff's device failed; %d", rc);
    check(valid_copy(to, count, 'x'), "Duff's device failed copy.");

    //reset
    memset(to, 'y', count);

    //my version
    rc = zeds_device(from, to, count);
    check(rc == count, "Zed's device faild: %d", rc);
    check(valid_copy(to, count, 'x'), "Zed's device failed copy.");

    double duffs_time = testPerfomance(from, to, count, duffs_device);
    double normal_time = testPerfomance(from, to, count, normal_copy);
    printf("\nTimeD: %f\n", duffs_time);
    printf("TimeN: %f\n", normal_time);
    return 0;
error:
    return 1;
}

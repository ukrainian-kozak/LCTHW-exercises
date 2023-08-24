#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

double testPerfomance(char *from, char *to, int count, void* (*function)(void*, const void*, size_t))
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    function(to, from, count);
    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}

int main(int argc, char* argv[])
{
    int count = 10000000;

    char* from = (char*)malloc(count * sizeof(char));
    char* to_memcpy = (char*)malloc(count * sizeof(char));
    char* to_memmove = (char*)malloc(count * sizeof(char));
    char* to_memset = (char*)malloc(count * sizeof(char));

    if (!from || !to_memcpy || !to_memmove || !to_memset) {
        printf("Memory allocation is failed\n");
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        from[i] = 'a';
    }

    double memcpy_time = testPerfomance(from, to_memcpy, count, memcpy);

    double memmove_time = testPerfomance(from, to_memmove, count, memmove);

    double(memset_time);
    clock_t start, end;
    start = clock();
    memset(to_memset, 'b', count);
    end = clock();
    memset_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time atken by memcpy: %f seconds\n", memcpy_time);
    printf("Time taken by memmove: %f seconds\n", memmove_time);
    printf("Time taken by memset: %f seconds\n", memset_time);

    free(from);
    free(to_memcpy);
    free(to_memmove);
    free(to_memset);

    return 0;
}



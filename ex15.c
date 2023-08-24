#include <stdio.h>
#include <stdlib.h>

void printArray(char** str, const int nums[], int size) 
{
    for (int i = 0; i < size; ++i) {
        printf("%s hsd %d year old.\n", str[i], nums[i]);
    }

    int i = 0;
    while (i < size) {
        printf("%s has %d years old.\n", str[i], nums[i]);
        ++i;
    }
}

int main(int argc, char* argv[]) 
{
    //create two array we care about
    int ages[] = { 23, 43, 12, 89, 2 };
    
    //int count = 5;
    //int* ages = malloc(count*sizeof(int));
    /*if (ages) {
        ages[0] = 23;
        ages[1] = 43;
        ages[2] = 12;
        ages[3] = 89;
        ages[4] = 2;
    }*/

    char* names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    //char** pnames = names;
    
    //safely get the size of ages
    int count = sizeof(ages) / sizeof(ages[0]);
    int i = 0;

    //first way using indexing
    for (i = 0; i < count; ++i) {
        printf("%s has %d year alive.\n", names[i], ages[i]);
    }

    printf("---\n");

    //set up the pointers to the start of the arrays
    //int* cur_age = ages;
    //char **cur_name = names;

    //second way using pointers
    /*for (i = count - 1; i >= 0; --i) {
        printf("%s is %d years old.\n",
                *(cur_name + i), *(cur_age + i));
    }

    printf("---\n");

    //third way, poinetrs are just arrays
    for (i = 0; i < count; ++i) {
        printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
    }

    printf("---\n");

    //fourth way with pointers in a stupid complex way
    for (cur_name = names + count - 1, cur_age = ages + count - 1;
            (cur_age - ages) >= 0; --cur_name, --cur_age) {
        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
    }
    
    free(ages);*/

    int* cur_ages = ages;
    char** cur_name = names;
    for (i = 0; i < count; ++i) {
        printf("Address of %d age: %5p\naddress of %d name: %5p\n", i, cur_ages + i, i, cur_name + i);
    }

    printArray(names, ages, count);

    return 0;
}

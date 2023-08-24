#include <stdio.h>

int main(int argc, char* argv[])
{
    char* arr[] = {"so", "I", "lol"};
    char** parr = arr;
    int i = 25;
    while (i > 0) {
        printf("%d", i);
        --i;
    }    

    return 0;
}

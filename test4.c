#include <stdio.h>

typedef union {
    int a;
    char b;
    double c;
} data;

int main(int argc, char* argv[])
{
    data arr[10];
    arr[0].a = 12;
    arr[1].b = 'a';
    arr[2].c = 13.56;
    printf("%d\n%c\n%f\n", arr[0].a, arr[1].b, arr[2].c);
    
    return 0;
}

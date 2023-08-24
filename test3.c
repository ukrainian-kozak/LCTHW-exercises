#include <stdio.h>


typedef struct {
    short field1;
    int field2;
    char fiel1; 
} Thing;


int main(int argc, char *argv[]) 
{
    int a = 10;
    double b = 2.0;
    int c = (int)b + a;
    printf("%d", c);
}

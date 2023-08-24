#include <stdio.h>

int main(int argc, char* argv[]) 
{
    int areas[] = { 10, 12, 13, 14, 20 };
    char name[] = "Zed";
    char full_name[] = {
        'Z', 'e', 'd',
        ' ', 'A', '.', ' ',
        'S', 'h', 'a', 'w'
    };

    //WARNING: On some system you may have to change the
    //%ld in this code to a %u since it will unsigned ints
    printf("The size of an int: %lu\n", sizeof(int));
    printf("The size of areas (int[]): %lu\n", sizeof(areas));
    printf("The number of ints in areas: %lu\n", 
            sizeof(areas) / sizeof(int));
    printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);

    printf("The size of a char: %lu\n", sizeof(char));
    printf("The size of name (char[]): %lu\n", sizeof(name));
    printf("The number of chars: %lu\n", sizeof(name) / sizeof(char));

    printf("The size of full_name (char[]) is %lu\n", sizeof(full_name));
    printf("The number of chars: %lu\n", 
            sizeof(full_name) / sizeof(char));

    printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);

    return 0;
}

#include <stdio.h>

FILE *stream;

int main(int argc, char *argv[])
{
    fpos_t pos;
    int retcode;

    stream = fopen("mylib\myfile", "rb");

    if ((retcode = fgetpos(stream, &pos)) == 0) 
        printf("Current position of file pointer found\n");
    fclose(stream);
}

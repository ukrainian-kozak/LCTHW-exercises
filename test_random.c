#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 16 

int main(int argc, char* argv[])
{
    FILE *urand = fopen("/dev/urandom", "rb"); 
    if (urand == NULL) {
        perror("Failed to open /dev/urandom");
        return 1;
    }

    char rand_string[BUFFER_SIZE];
    size_t bytes_read = fread(rand_string, 1, sizeof(rand_string), urand);

    if (bytes_read != sizeof(rand_string)) {
        perror("Error reading from /dev/urandom");
        fclose(urand);
        return 1;
    }

    printf("Random string: ");
    for (size_t i = 0; i < sizeof(rand_string); ++i) {
        printf("%02x", (unsigned char)rand_string[i]);
    }
    printf("\n");

    fclose(urand);
    return 0;
}

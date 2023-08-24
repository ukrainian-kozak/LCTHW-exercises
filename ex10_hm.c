#include <stdio.h>
#include <string.h>



void removeChar(char* str, char garbage)
{
    char* src;
    char* dst;
    for (src = dst = str; *src != '\0'; ++src) {
        *dst = *src;
        if (*src != garbage) {
            ++dst;
        }
    }
    *dst = '\0';
}

int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        printf("ERROR: You must have 2 arguments.\n");
        return 1;
    }
    
    char string[100];
    for (int i = 0; argv[1][i] != '\0'; ++i)  {
        char letter = argv[1][i];
        switch (letter) {
            
            case 'A': string[i] = 'A' + 32; argv[1][i] = ' ';  break; 
            case 'B': string[i] = 'B' + 32; argv[1][i] = ' ';  break; 
            case 'C': string[i] = 'C' + 32; argv[1][i] = ' ';  break; 
            case 'D': string[i] = 'D' + 32; argv[1][i] = ' ';  break; 
            case 'E': string[i] = 'E' + 32; argv[1][i] = ' ';  break; 
            case 'F': string[i] = 'F' + 32; argv[1][i] = ' ';  break; 
            case 'G': string[i] = 'G' + 32; argv[1][i] = ' ';  break; 
            case 'H': string[i] = 'H' + 32; argv[1][i] = ' ';  break; 
            case 'I': string[i] = 'I' + 32; argv[1][i] = ' ';  break; 
            case 'J': string[i] = 'J' + 32; argv[1][i] = ' ';  break; 
            case 'K': string[i] = 'K' + 32; argv[1][i] = ' ';  break; 
            case 'L': string[i] = 'L' + 32; argv[1][i] = ' ';  break; 
            case 'M': string[i] = 'M' + 32; argv[1][i] = ' ';  break; 
            case 'N': string[i] = 'N' + 32; argv[1][i] = ' ';  break; 
            case 'O': string[i] = 'O' + 32; argv[1][i] = ' ';  break; 
            case 'P': string[i] = 'P' + 32; argv[1][i] = ' ';  break; 
            case 'Q': string[i] = 'Q' + 32; argv[1][i] = ' ';  break; 
            case 'R': string[i] = 'R' + 32; argv[1][i] = ' ';  break; 
            case 'S': string[i] = 'S' + 32; argv[1][i] = ' ';  break; 
            case 'T': string[i] = 'T' + 32; argv[1][i] = ' ';  break; 
            case 'U': string[i] = 'U' + 32; argv[1][i] = ' ';  break; 
            case 'V': string[i] = 'V' + 32; argv[1][i] = ' ';  break; 
            case 'W': string[i] = 'W' + 32; argv[1][i] = ' ';  break; 
            case 'X': string[i] = 'X' + 32; argv[1][i] = ' ';  break; 
            case 'Y': string[i] = 'Y' + 32; argv[1][i] = ' ';  break; 
            case 'Z': string[i] = 'Z' + 32; argv[1][i] = ' ';  break;
            default: string[i] = argv[1][i];  break;
                      
        }

        printf("Before: %s\n", argv[1]);
        printf("After: %s\n", string);
    
    }

    return 0;
}

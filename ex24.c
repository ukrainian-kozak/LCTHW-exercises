#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include <stdlib.h>

#define MAX_DATA 100

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, DROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Blsck", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

void print_smth(char *str, int size)
{
    int  i =0;

    for (i = 0; i <= size; ++i) {
        scanf("%c", &str[i]);
    }
     int ch;
     while ((ch = getchar()) != '\n' && ch != EOF);
     printf("%s", str);
}

int main(int argc, char *argv[])
{
    Person you = {.age = 0 };
    int i = 0;
    char *in = NULL;

    int size;
    printf("Enter the size: ");
    scanf("%d", &size);
    char* str = malloc(sizeof(char) * size);
    print_smth(str, size);
    
    //int ch;
     //while ((ch = getchar()) != '\n' && ch != EOF);

    printf("What's your First Name? ");
    in = fgets(you.first_name, MAX_DATA - 1, stdin);
    check(in != NULL, "Failed to read first name.");
    you.first_name[strlen(you.first_name) - 1] = '\0';

    printf("What's your Last Name? ");
    in = fgets(you.last_name, MAX_DATA - 1, stdin);
    check(in != NULL, "Failed to read last name.");
    you.last_name[strlen(you.last_name) - 1] = '\0';

    printf("How old are you? ");
    int rc = fscanf(stdin, "%d", &you.age);
    check(rc > 0, "You have ti enter a number. ");

    printf("What color are your eyes:\n");
    for (i = 0; i <= OTHER_EYES; ++i) {
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "You have to enter a number.");

    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES
                && you.eyes >= 0, "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "Enter a floating point number.");

    printf("----RESULTS----\n");

    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;
error:

    return -1;
}

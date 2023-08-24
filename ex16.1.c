#include <stdio.h>

struct Person {
    char* name;
    int age;
    int height;
    int weight;
};

struct Person Person_create(char* name, int age, int height, int weight) 
{
    struct Person who;
    who.name = name;
    who.age = age;
    who.height = height;
    who.weight = weight;

    return who;
}

void Person_print(struct Person who) 
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\tHeight: %d\n", who.height);
    printf("\tWeight: %d\n", who.weight);
}


int main(int argc, char* argv[]) 
{
    struct Person joe = Person_create("Joe", 18, 180, 80);
    printf("Joe was created.\n");
    Person_print(joe);

    struct Person frank = Person_create("Frank", 30, 170, 60);
    printf("Frank was created.\n");
    Person_print(frank);

    joe.age += 2;
    joe.height += 2;
    joe.weight += 10;
    Person_print(joe);

    frank.age += 2;
    frank.weight += 10;
    Person_print(frank);

    return 0;   
}

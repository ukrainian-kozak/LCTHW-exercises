#include <stdio.h>


int main(int args, char* argv[]) {
    int distance = 100;
    float power = 2.345f;
    double super_power = 5678.4532;
    char initial = 'A';
    char* first_name = "Zved";
    char* last_name = "Shaw";
    //char nul = '\0';

    printf("You are %d miles away.\n", distance);
    printf("You are %f levels of power.\n", power);
    printf("You have %f awesome super powers.\n", super_power);
    printf("I have an initial %c.\n", initial);
    printf("I have a first name %s.\n", first_name);
    printf("I have a last name %s.\n", last_name);
   // printf("My whole name is %s %c. %s.\n",
   //         nul, nul, nul);
    
    int bugs = 100;
    double bug_rate = 1.2;

    printf("You have %d bugs at the imaginary rate of %f.\n", 
            bugs, bug_rate);

    unsigned long universe_of_defects = 100050432567049387 * 10223234L * 10233324L * 123024L * 1232024L * 123456789L * 1234567L * 1234567890L;
    printf("The untire universe has %lu bugs.\n",
            universe_of_defects);

    double expected_bugs = bugs * bug_rate;
    printf("You are expected to have %f bugs.\n",
            expected_bugs);

    double part_of_universe = expected_bugs / universe_of_defects;
    printf("That is only a %e portion of the unirese.\n",
            part_of_universe);

    //this makees no sense, just a demo of something weird
    char nul_byte = '\0';
    int care_percentage = bugs * nul_byte;
    printf("Which means you should care %d%%.\n", 
            care_percentage);

    return 0;
}

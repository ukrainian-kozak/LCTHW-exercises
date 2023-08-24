#include <stdio.h>

#define MAX_SIZE 100

struct Stack {
    int top;
    int elements[MAX_SIZE];
};

struct Stack stack;

void Push(int value)
{
    ++stack.top;
    stack.elements[stack.top] = value;
}

void Pop() 
{
    --stack.top;
}

int Top() 
{
    if (stack.top == 0) {
        printf("Stack is empty!\n");
        return 0;
    }
    return stack.elements[stack.top];
}

int main(int argc, char *argv[])
{
    stack.top = 0;
    Push(1);
    Push(2);
    Push(3);

    while(stack.top != 0) {
        printf("%d\n", Top());
        Pop();
    }

    return 0;
}

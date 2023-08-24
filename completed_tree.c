#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *newNode(int data)
{
    struct Node *temp = (struct Node *) malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int number(struct Node *root)
{
    if (!root)
        return 0;
    return (1 + number(root->left) + number(root->right));
}


bool checkComplete(struct Node *root, int index, int numberNodes)
{
    if (!root)
        return true;

    if (index >= numberNodes)
        return false;

    return (checkComplete(root->left, 2 * index + 1, numberNodes) && checkComplete(root->right, 2 * index + 2, numberNodes));
}



int main(int argc, char *argv[])
{
    struct Node *root = NULL;
    root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);

    int index = 0;
    int numberNodes = number(root);

    if (checkComplete(root, index, numberNodes))
        printf("Tree is completed");
    else
        printf("Tree is not completed");
}

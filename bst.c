#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

struct Node *newNode(int data)
{
    struct Node *temp = (struct Node *) malloc(sizeof(struct Node));
    temp->key = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

void inorder(struct Node *root)
{
    if (!root)
        return;
    inorder(root->left);
    printf("-> %d", root->key);
    inorder(root->right);
}

int search(struct Node *root, int target)
{
    if (!root)
        return 0;
    if (target == root->key)
        return root->key;
    if (target > root->key)
        return search(root->right, target);
    if (target < root->key)
        return search(root->left, target);
    return 0;
}

struct Node *insert(struct Node *root, int data)
{
    if (!root)
        return newNode(data);
    if (root->key > data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);
    return root;
}

struct Node *minElem(struct Node *root)
{
    struct Node *curr = root;
    while (curr && curr->left)
        curr = curr->left;
    return curr;
}

struct Node *delete(struct Node *root, int key)
{
    if (!root)
        return NULL;
    if (root->key < key)
        root->right = delete(root->right, key);
    else if (root->key > key)
        root->left = delete(root->left, key);
    else {
        if (!root->left) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        struct Node *temp = minElem(root->right);
        root->key = temp->key;
        root->right = delete(root->right, temp->key);
    }
    return root;
}

int main(int argc, char *argv[])
{
    struct Node *root = NULL;
    root = insert(root, 8);
    root = insert(root, 3);
    root = insert(root, 1);
    root = insert(root, 10);
    root = insert(root, 6);
    root = insert(root, 7);
    root = insert(root, 14);
    root = insert(root, 4);

    printf("Inorder traversal: ");
    inorder(root);
    delete(root, 8);
    inorder(root);

    return 0;
}



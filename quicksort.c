#include <stdio.h>

static inline void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int array[], int low, int high)
{
    int pivot = array[high];
    int p_pos = (low - 1);

    for (int i = low; i < high; ++i) {
        if (array[i] <= pivot) {
            ++p_pos;
            swap(&array[i], &array[p_pos]);
        }
    }

    swap(&array[p_pos + 1], &array[high]);

    return (p_pos + 1);
}

void qsort(int array[], int low, int high)
{
    if (low < high) {
        int pi = partition(array, low, high);
        qsort(array, low, pi - 1);
        qsort(array, pi + 1, high);
    }
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }

    printf("\n");
}


int main(int argc, char* argv[])
{
    int array[10] = { 9 ,5 ,6, 3, 2, 1, 4, 7, 8 ,0 };
    int size = sizeof(array) / sizeof(int);

    printArray(array, size);
    qsort(array, 0, size - 1);
    printArray(array, size);
}

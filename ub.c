#include <stdio.h>

//int main() {
//    int *ptr;
//    {
//        int x = 10;
//        ptr = &x;
//    }
//
//    printf("%d\n", *ptr);
//
//    return 0;
//}

//int* get_pointer() {
//    int x = 5;
//    return &x;
//}
//
//int main() {
//    int* ptr = get_pointer();
//
//    printf("%d\n", *ptr);
//
//    return 0;
//}

//int main() {
//    int x;
//
//    printf("%d\n", x);
//
//    return 0;
//}

//int main() {
//    int num = 1000;
//    char c = num;
//
//    printf("The value of c: %d\n", c);
//
//    return 0;
//}

//int main() {
//    double largeNum = 1.0e100;
//    float smallNum = largeNum;
//
//    printf("The avlue float: %f\n", smallNum);
//
//    return 0; 
//}

//int func(int x) {
//    return x + 1;
//}
//
//float func(float y) {
//    return y + 1.0;
//}
//
//int main() {
//    int a = 10;
//    float b = 5.5;
//
//    printf("Result 1: %d\n", func(a));
//    printf("Result 2: %f\n", func(b));
//
//    return 0;
//}

//int main() {
//    char* str = "Hello, world";
//
//    str[1] = 'h';
//
//    printf("%s\n", str);
//
//    return 0;
//}

//int add(int a, int b) {
//    return a + b;
//}
//
//int main() {
//    add(2, 3) = 10;
//
//    return 0;
//}

//int main() {
//    int a  = 10;
//    int b = 0;
//    int result = a / b;
//
//    printf("Result: %d", result);
//
//    return 0;
//}

//int main() {
//    int arr[5] = {1,2,3,4,5};
//    double* ptr = (double*)arr;
//
//    arr[0] = 3.14;
//
//    printf("%lf",ptr[0]);
//
//    return 0;
//}

//int main() {
//    const int x = 5;
//    int* ptr = &x;
//
//    *ptr = 10;
//
//    printf("Modified value: %d\n", x);
//
//    return 0;
//}

inline int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(2,3);

    printf("Result: %d\n", result);

    return 0;
}

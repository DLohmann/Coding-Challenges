#include<stdio.h>

// Write a C program that prints the numbers 1 to 100. For multiples of three print the string “Fizz” instead of the number.
// For multiples of five print the string “Buzz” instead of the number.
// For multiples of both three and five, print the string FizzBuzz instead of the number.

void FizzBuzz(int n) {
    for (int i = 1; i <= n; i++) {
        if (i % 3 != 0 && i % 5 != 0) {
            printf("%d\n", i);
            continue;
        }
        if (i % 3 == 0) {
            printf("Fizz");
        }
        if (i % 5 == 0) {
            printf("Buzz");
        }
        printf("\n");
    }
}

int main() {
    FizzBuzz(100);
    return 0;
}

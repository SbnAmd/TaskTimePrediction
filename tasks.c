#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include "def.h"
#include "tasks.h"
#define ARRAY_SIZE 10000

Func task_array[NUM_THREADS] ={
    benchmark_fibonacci,
    benchmark_sqrt_math,
    benchmark_memory_allocation,
    benchmark_string_processing,
    benchmark_matrix_multiplication,
    benchmark_file_io,
    benchmark_bitwise_operations,
    benchmark_random_numbers,
    benchmark_prime_check,
    benchmark_sorting,
 };


// Fibonacci
uint64_t fib(int n){
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

void benchmark_fibonacci() {
    fib(30);
}

// SQRT
void benchmark_sqrt_math() {
    double result = 0.0;
    for (int i = 1; i < 100000; ++i) {
        result += sqrt(i) * log(i);
    }
    // printf("Math result: %f\n", result);
}

// Memory Allocation
void benchmark_memory_allocation() {
    int *arr = malloc(ARRAY_SIZE * sizeof(int));
    if (!arr) return;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = i * i;
    }
    free(arr);
}

// String Processing
void benchmark_string_processing() {
    char *text = strdup("The quick brown fox jumps over the lazy dog");
    for (int i = 0; i < strlen(text); ++i) {
        if (text[i] >= 'a' && text[i] <= 'z') text[i] -= 32;
    }
    free(text);
}

// Matrix Multiplication
void benchmark_matrix_multiplication() {
    int a[50][50], b[50][50], c[50][50];
    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 50; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
        }

    for (int i = 0; i < 50; i++)
        for (int j = 0; j < 50; j++) {
            c[i][j] = 0;
            for (int k = 0; k < 50; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
}

// File I/O
void benchmark_file_io() {
    FILE *fp = tmpfile();
    if (!fp) return;
    for (int i = 0; i < 1000; ++i) {
        // fprintf(fp, "Line %d: Benchmark file I/O test.\n", i);
    }
    rewind(fp);
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), fp)) {}
    fclose(fp);
}

// Bitwise Operations
void benchmark_bitwise_operations() {
    uint64_t x = 0x12345678ABCDEF00;
    for (int i = 0; i < 1000000; ++i) {
        x ^= (x << 13);
        x ^= (x >> 7);
        x ^= (x << 17);
    }
}

// Random Numbers
void benchmark_random_numbers() {
    srand((unsigned)time(NULL));
    double sum = 0.0;
    for (int i = 0; i < 100000; ++i) {
        sum += rand() / (double)RAND_MAX;
    }
    // printf("Random sum: %f\n", sum);
}

// Prime Numbers
bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

void benchmark_prime_check() {
    for (int i = 2; i < 10000; ++i) {
        is_prime(i);
    }
}

// Sorting
void quicksort(int *a, int low, int high) {
    if (low < high) {
        int pivot = a[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (a[j] < pivot) {
                i++;
                int tmp = a[i]; a[i] = a[j]; a[j] = tmp;
            }
        }
        int tmp = a[i + 1]; a[i + 1] = a[high]; a[high] = tmp;
        quicksort(a, low, i);
        quicksort(a, i + 2, high);
    }
}

void benchmark_sorting() {
    int *arr = malloc(ARRAY_SIZE * sizeof(int));
    if (!arr) return;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = rand() % 100000;
    }
    quicksort(arr, 0, ARRAY_SIZE - 1);
    free(arr);
}

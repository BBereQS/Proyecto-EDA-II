#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <iso646.h>
#include <time.h>

#define NUM_ELEMS 5000
#define MAX 50

void print(int* list, size_t tam, char* msg);
void swap(float* val1, float* val2);
void quick_sort(float list[], size_t first, size_t last);

#endif /* QUICKSORT_H */

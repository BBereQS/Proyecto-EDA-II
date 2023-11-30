
#ifndef BUSQUEDAB_H
#define BUSQUEDAB_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <omp.h>
#include "Grafos.h"

void swap_b(Restaurante* val1, Restaurante* val2);
void heapify(Restaurante list[], size_t n, size_t root);
void build_max_heap(Restaurante list[], int num_elems);
void heap_sort(Restaurante list[], int num_elems);
bool binary_search_stars(Restaurante list[], int len, int key, char* found_name);

#endif
#ifndef SORTERS_H
#define SORTERS_H

#include "utils.h"

int partition  (void* arr, size_t elem_size, int low, int high,
                int (*compare_func)(void*, void*, size_t));
void quick_sort(void* arr, size_t elem_size, int low, int high,
                int (*compare_func)(void*, void*, size_t));
void sort_onegin(struct DiffSortedText* text, int strings_number);

#endif

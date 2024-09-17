#include <assert.h>

#include "comparators.h"
#include "sorters.h"
#include "utils.h"


int partition(void* arr, size_t elem_size, int low, int high,
              int (*compare_func)(void*, void*, size_t))
{
    assert(low <= high);

    void* p = (char*) arr + low*elem_size;
    int i = low;
    int j = high;

    while (i < j)
    {
        assert(i >= low);
        assert(j <= high);

        while (compare_func((char*) arr + i*elem_size, p, elem_size) <= 0 && i <= high - 1)
            i++;

        while (compare_func((char*) arr + j*elem_size, p, elem_size) > 0 && j >= low + 1)
            j--;

        if (i < j)
            swap((char*) arr + i*elem_size, (char*) arr + j*elem_size, elem_size);
    }

    swap((char*) arr + low*elem_size, (char*) arr + j*elem_size, elem_size);
    return j;
}


void quick_sort(void* arr, size_t elem_size, int low, int high,
                int (*compare_func)(void*, void*, size_t))
{
    if (low < high)
    {
        int pi = partition(arr, elem_size, low, high, compare_func);
        assert(pi >= low);
        assert(pi <= high);

        quick_sort(arr, elem_size, low,    pi - 1, compare_func);
        quick_sort(arr, elem_size, pi + 1, high,   compare_func);
    }
}


void sort_onegin(struct DiffSortedText* text, int strings_number)
{
    const int START_OF_MAS = 0, END_OF_MAS = strings_number - 1;
    quick_sort(text->dir_sort, sizeof(text->dir_sort[0]), START_OF_MAS, END_OF_MAS, compare_direct);
    quick_sort(text->rev_sort, sizeof(text->rev_sort[0]), START_OF_MAS, END_OF_MAS, compare_reverse);
}

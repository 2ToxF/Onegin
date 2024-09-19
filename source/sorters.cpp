#include <assert.h>

#include "comparators.h"
#include "sorters.h"
#include "utils.h"

static int partition  (void* arr, size_t elem_size, int low_border, int high_border,
                       int (*compare_func)(void*, void*));
static void quick_sort(void* arr, size_t elem_size, int low_border, int high_border,
                       int (*compare_func)(void*, void*));


int partition(void* arr, size_t elem_size, int low_border, int high_border,
              int (*compare_func)(void*, void*))
{
    assert(low_border <= high_border);

    void* separator_elem = (char*) arr + low_border*elem_size;
    // low_border, high_border
    int low = low_border;
    int high = high_border;

    while (low < high)
    {
        assert(low >= low_border);
        assert(high <= high_border);

        while (compare_func((char*) arr + low*elem_size, separator_elem) <= 0 && low <= high_border - 1)
            low++;

        while (compare_func((char*) arr + high*elem_size, separator_elem) > 0 && high >= low_border + 1)
            high--;

        if (low < high)
            swap((char*) arr + low*elem_size, (char*) arr + high*elem_size, elem_size);
    }

    swap((char*) arr + low_border*elem_size, (char*) arr + high*elem_size, elem_size);
    return high;
}


void quick_sort(void* arr, size_t elem_size, int low_border, int high_border,
                int (*compare_func)(void*, void*))
{
    if (low_border < high_border)
    {
        int separator_idx = partition(arr, elem_size, low_border, high_border, compare_func);
        assert(separator_idx >= low_border);
        assert(separator_idx <= high_border);

        quick_sort(arr, elem_size, low_border,        separator_idx - 1, compare_func);
        quick_sort(arr, elem_size, separator_idx + 1, high_border,       compare_func);
    }
}


void sort_onegin(struct DiffSortedText* text, int strings_number)
{
    const int START_OF_MAS = 0, END_OF_MAS = strings_number - 1;
    quick_sort(text->dir_sort, sizeof(text->dir_sort[0]), START_OF_MAS, END_OF_MAS, compare_direct);
    quick_sort(text->rev_sort, sizeof(text->rev_sort[0]), START_OF_MAS, END_OF_MAS, compare_reverse);
}

#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

#define FREE(buffer) free(buffer); buffer = NULL;
#define FCLOSE(fptr) fclose(fptr); fptr = NULL;

struct StringStat
{
    char* adress;
    int len;
};
struct DiffSortedText
{
    char**              dir_sort;
    struct StringStat*  rev_sort;
    char**              no_sort;
};

int get_strings_number(char* input_buffer);
void read_strings(struct DiffSortedText* text, char* input_buffer, int input_buffer_length);
void swap(void* x, void* y, size_t var_size);

#endif

#ifndef UTILS_H
#define UTILS_H

//#include <stddef.h>
#include <stdio.h>

#define FREE(buffer)  { free(buffer); (buffer) = NULL; }
#define FCLOSE(fptr)  { fclose(fptr); (fptr)   = NULL; }

enum CodeError
{
    NO_ERROR,
    FILLING_STAT_ERROR,
    FILE_NOT_OPENED_ERROR,
    WRONG_BUF_SIZE_ERROR,
};

struct StringStat
{
    char* adress;
    int len;
};
struct DiffSortedText  // think about it
{
    char**              dir_sort;
    struct StringStat*  rev_sort;
    char**              no_sort;
};

CodeError fsize(const char* file_name, int* input_buffer_length);
int get_strings_number(char* input_buffer);
void read_strings(struct DiffSortedText* text, char* input_buffer, int input_buffer_length);
void swap(void* x, void* y, size_t var_size);

#endif

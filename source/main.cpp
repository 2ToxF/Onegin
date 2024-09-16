#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>
#include <unistd.h>

#define FREE(buffer) free(buffer);
#define FCLOSE(fptr) fclose(fptr); fptr = NULL;

struct StringStat
{
    char* adress;
    int len;
};

int compare_direct (struct StringStat strstat1, struct StringStat strstat2);
int compare_reverse(struct StringStat strstat1, struct StringStat strstat2);
int partition(struct StringStat* arr, int low, int high,
              int (*compare_func)(struct StringStat, struct StringStat));
void quick_sort (struct StringStat* arr, int low, int high,
                 int (*compare_func)(struct StringStat, struct StringStat));
void swap(struct StringStat* x, struct StringStat* y);

int main()
{
    const char* const FILE_INPUT_NAME = "onegin.txt";
    const char* const FILE_RESULT_NAME = "result.txt";

    const int CR_TARGET = '\r';
    const int NULL_TARGET = '\0';

    const int NUM_OF_ACTIONS_PER_CHAR = 1;

    struct stat input_file_stat = {};
    if (stat(FILE_INPUT_NAME, &input_file_stat) != 0)
    {
        printf("ERROR: FILLING \"STRUCT STAT\" WAS FAILED\n");
        return -1;
    }
    int input_buffer_length = input_file_stat.st_size + 1;

    FILE* input_fptr = fopen(FILE_INPUT_NAME, "rb");
    if (input_fptr == NULL)
    {
        printf("ERROR: FILE NOT OPENED\n");
        return -1;
    }

    char* input_buffer = (char*) calloc(input_buffer_length, sizeof(char));
    long long unsigned int success_read_string_length = fread(input_buffer, NUM_OF_ACTIONS_PER_CHAR,
                                                              input_file_stat.st_size, input_fptr);
    if (success_read_string_length != (long long unsigned int) input_file_stat.st_size)
    {
        printf("ERROR: WRONG SIZE OF INPUT BUFFER\n");
        printf("read: %llu; expected: %ld\n", success_read_string_length, input_file_stat.st_size);
        return -1;
    }
    FCLOSE(input_fptr)

    int strings_number = 0;
    char* last_str_ptr = input_buffer;
    while ((last_str_ptr = strchr(last_str_ptr, CR_TARGET)) != NULL)
    {
        *last_str_ptr++ = '\n'; *last_str_ptr++ = '\0';
        strings_number++;
    }

    struct StringStat* not_sorted_strings = (struct StringStat*) calloc((size_t) strings_number, sizeof(StringStat));
    struct StringStat* dir_sorted_strings = (struct StringStat*) calloc((size_t) strings_number, sizeof(StringStat));
    struct StringStat* rev_sorted_strings = (struct StringStat*) calloc((size_t) strings_number, sizeof(StringStat));

    int read_strings_number = 0;
    char* const max_buffer_adress = input_buffer + input_buffer_length - 1;
    last_str_ptr = input_buffer;
    char* new_str_ptr = input_buffer;

    while(true)
    {
        new_str_ptr = strchr(last_str_ptr, NULL_TARGET) + 1;

        not_sorted_strings[read_strings_number] = dir_sorted_strings[read_strings_number] = \
            rev_sorted_strings[read_strings_number] = {last_str_ptr, (int) (new_str_ptr - last_str_ptr)};
        last_str_ptr = new_str_ptr;
        read_strings_number++;

        if (new_str_ptr == max_buffer_adress)
            break;
    }

    const int START_OF_MAS = 0, END_OF_MAS = strings_number - 1;
    quick_sort(dir_sorted_strings, START_OF_MAS, END_OF_MAS, compare_direct);
    quick_sort(rev_sorted_strings, START_OF_MAS, END_OF_MAS, compare_reverse);

    FILE* result_fptr = fopen(FILE_RESULT_NAME, "w");

    for (int i = 0; i < strings_number; i++)
        fprintf(result_fptr, "%s", (dir_sorted_strings[i]).adress);
    fprintf(result_fptr, "\n\n-----------------------------------------------------------------------\n\n\n");

    for (int i = 0; i < strings_number; i++)
        fprintf(result_fptr, "%s", rev_sorted_strings[i].adress);
    fprintf(result_fptr, "\n\n-----------------------------------------------------------------------\n\n\n");

    for (int i = 0; i < strings_number; i++)
        fprintf(result_fptr, "%s", not_sorted_strings[i].adress);

    return 0;
}


int compare_direct(struct StringStat strstat1, struct StringStat strstat2)
{
    int s1ind = 0, s2ind = 0;
    while (s1ind < strstat1.len && s2ind < strstat2.len)
    {
        if (isalpha(strstat1.adress[s1ind]) == 0)
        {
            s1ind++;
            continue;
        }
        if (isalpha(strstat2.adress[s2ind]) == 0)
        {
            s2ind++;
            continue;
        }

        if (toupper(strstat1.adress[s1ind]) != toupper(strstat2.adress[s2ind]))
            return toupper(strstat1.adress[s1ind]) - toupper(strstat2.adress[s2ind]);

        s1ind++; s2ind++;
    }

    return s2ind - s1ind;
}


int compare_reverse(struct StringStat strstat1, struct StringStat strstat2)
{
    int s1ind = strstat1.len - 1, s2ind = strstat2.len - 1;
    while (s1ind >= 0 && s2ind >= 0)
    {
        if (isalpha(strstat1.adress[s1ind]) == 0)
        {
            s1ind--;
            continue;
        }
        if (isalpha(strstat2.adress[s2ind]) == 0)
        {
            s2ind--;
            continue;
        }

        if (toupper(strstat1.adress[s1ind]) != toupper(strstat2.adress[s2ind]))
            return toupper(strstat1.adress[s1ind]) - toupper(strstat2.adress[s2ind]);

        s1ind--; s2ind--;
    }

    return s1ind - s2ind;
}


int partition(struct StringStat* arr, int low, int high,
              int (*compare_func)(struct StringStat, struct StringStat))
{
    struct StringStat p = arr[low];
    int i = low;
    int j = high;

    while (i < j)
    {
        while (compare_func(arr[i], p) <= 0 && i <= high - 1)
            i++;

        while (compare_func(arr[j], p) > 0 && j >= low + 1)
            j--;

        if (i < j)
            swap(&arr[i], &arr[j]);
    }

    swap(&arr[low], &arr[j]);
    return j;
}


void quick_sort(struct StringStat* arr, int low, int high,
                int (*compare_func)(struct StringStat, struct StringStat))
{
    if (low < high)
    {
        int pi = partition(arr, low, high, compare_func);

        quick_sort(arr, low, pi - 1, compare_func);
        quick_sort(arr, pi + 1, high, compare_func);
    }
}


void swap(struct StringStat* x, struct StringStat* y)
{
    struct StringStat tmp = *x;
    *x = *y;
    *y = tmp;
    return;
}

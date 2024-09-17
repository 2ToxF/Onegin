#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys\stat.h>
#include <unistd.h>

#define FREE(buffer) free(buffer); buffer = NULL;
#define FCLOSE(fptr) fclose(fptr); fptr = NULL;

struct StringStat
{
    char* adress;
    int len;
};

const char* const FILE_INPUT_NAME  = "test.txt";
const char* const FILE_RESULT_NAME = "result.txt";
const int CR_TARGET   = '\r';
const int NULL_TARGET = '\0';
const int NUM_OF_ACTIONS_PER_CHAR = 1;

int compare_direct (void* void_strstat1, void* void_strstat2, size_t);
int compare_reverse(void* void_strstat1, void* void_strstat2, size_t);
int partition  (void* arr, size_t elem_size, int low, int high,
                int (*compare_func)(void*, void*, size_t));
void quick_sort(void* arr, size_t elem_size, int low, int high,
                int (*compare_func)(void*, void*, size_t));
void swap(void* x, void* y, size_t var_size);

int main()
{
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
    printf("direct sort"); getchar();
    quick_sort(dir_sorted_strings, sizeof(dir_sorted_strings[0]), START_OF_MAS, END_OF_MAS, compare_direct);
    //printf("reverse sort"); getchar();
    //quick_sort(rev_sorted_strings, sizeof(rev_sorted_strings[0]), START_OF_MAS, END_OF_MAS, compare_reverse);

    FILE* result_fptr = fopen(FILE_RESULT_NAME, "wb");

    for (int i = 0; i < strings_number; i++)
        fprintf(result_fptr, "%s", (dir_sorted_strings[i]).adress);
//     fprintf(result_fptr, "\n\n-----------------------------------------------------------------------\n\n\n");
//
//     for (int i = 0; i < strings_number; i++)
//         fprintf(result_fptr, "%s", rev_sorted_strings[i].adress);
//     fprintf(result_fptr, "\n\n-----------------------------------------------------------------------\n\n\n");
//
//     for (int i = 0; i < strings_number; i++)
//         fprintf(result_fptr, "%s", not_sorted_strings[i].adress);

    FCLOSE(result_fptr)
    FREE(dir_sorted_strings)
    FREE(rev_sorted_strings)
    FREE(not_sorted_strings)

    return 0;
}


int compare_direct(void* void_strstat1, void* void_strstat2, size_t)
{
    assert(void_strstat1 != NULL);
    assert(void_strstat2 != NULL);

    struct StringStat strstat1 = *((StringStat*) void_strstat1);
    struct StringStat strstat2 = *((StringStat*) void_strstat2);
    // printf("______----______\n");
    // printf("s1 = %ss2 = %s", strstat1.adress, strstat2.adress);
    // printf("______----______\n");
    int s1ind = 0, s2ind = 0;

    while (s1ind < strstat1.len && s2ind < strstat2.len)
    {
        //printf("chars = %d %d\n", strstat1.adress[s1ind], strstat2.adress[s2ind]);
        while (isalpha(strstat1.adress[s1ind]) == 0 && s1ind < strstat1.len)
            s1ind++;
        while (isalpha(strstat2.adress[s2ind]) == 0 && s2ind < strstat2.len)
            s2ind++;

        if (s1ind == strstat1.len || s2ind == strstat2.len)
            break;

        if (toupper(strstat1.adress[s1ind]) != toupper(strstat2.adress[s2ind]))
        {
            // printf("chars in result: %d %d\n", toupper(strstat1.adress[s1ind]), toupper(strstat2.adress[s2ind]));
            // printf("result1 = %d\n", toupper(strstat1.adress[s1ind]) - toupper(strstat2.adress[s2ind]));
            // getchar();
            return toupper(strstat1.adress[s1ind]) - toupper(strstat2.adress[s2ind]);
        }

        s1ind++; s2ind++;
    }
    // printf("indexes = %d %d\n", s1ind, s2ind);
    // printf("result2 = %d\n", s2ind - s1ind);
    // getchar();
    return s1ind - s2ind;
}


int compare_reverse(void* void_strstat1, void* void_strstat2, size_t)
{
    assert(void_strstat1 != NULL);
    assert(void_strstat2 != NULL);

    struct StringStat strstat1 = *((StringStat*) void_strstat1);
    struct StringStat strstat2 = *((StringStat*) void_strstat2);
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


int partition(void* arr, size_t elem_size, int low, int high,
              int (*compare_func)(void*, void*, size_t))
{
    assert(low <= high);

    void* p = (char*) arr + low*elem_size;
    // printf("-----------------------------------------------------------------");
    // getchar();
    // printf("p = %s", ((StringStat*) p)->adress);
    int i = low;
    int j = high;

    while (i < j)
    {
        assert(i >= low);
        assert(j <= high);
        //printf("!!! i = %d, j = %d !!!\n", i, j);
        //printf("strings to compare (i), res = %d:\n%s%s", compare_func((char*) arr + i*elem_size, p, elem_size), ((StringStat*) arr + i)->adress, ((StringStat*) p)->adress);
        //printf("%p %p\n", (char*) arr + i*elem_size, (StringStat*) arr + i);
        while (compare_func((char*) arr + i*elem_size, p, elem_size) <= 0 && i <= high - 1)
        {
//            printf("i = %d\n", i);
            i++;
        }

        //printf("strings to compare (j), res = %d:\n%s%s\n", compare_func((char*) arr + j*elem_size, p, elem_size), ((StringStat*) arr + j)->adress, ((StringStat*) p)->adress);
        while (compare_func((char*) arr + j*elem_size, p, elem_size) > 0 && j >= low + 1)
        {
//            printf("j = %d\n", j);
            j--;
        }

        if (i < j)
        {
//            printf("strings to swap 1:\n%s%s\n", ((StringStat*) arr + i)->adress, ((StringStat*) arr + j)->adress);
            swap((char*) arr + i*elem_size, (char*) arr + j*elem_size, elem_size);
        }
    }

//    printf("strings to swap 2:\n%s%s\n", ((StringStat*) arr + i)->adress, ((StringStat*) arr + j)->adress);
    swap((char*) arr + i*elem_size, (char*) arr + j*elem_size, elem_size);
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


void swap(void* x, void* y, size_t var_size)
{
    // void* x1 = x;
    // void* y1 = y;
    // printf("-------------- begin swap --------------");
    // printf("x before swap = %s", (*((StringStat*) x)).adress);
    // printf("y before swap = %s\n", (*((StringStat*) y)).adress);

//     typedef unsigned long long tmp_type1;
//     tmp_type1 tmp1 = 0;
//     while (var_size >= 8)
//     {
//         tmp1 = *((tmp_type1*) x);
//         *((tmp_type1*) x) = *((tmp_type1*) y);
//         *((tmp_type1*) y) = tmp1;
//
//         x = ((tmp_type1*) x) + 1; y = ((tmp_type1*) y) + 1;
//
//         var_size -= sizeof(tmp_type1);
//     }

    typedef char tmp_type2;
    tmp_type2 tmp2 = 0;
    for (size_t i = 0; i < var_size; i++)
    {
        tmp2 = *((tmp_type2*) x + i);
        *((tmp_type2*) x + i) = *((tmp_type2*) y + i);
        *((tmp_type2*) y + i) = tmp2;
    }

    // printf("x after swap = %s", (*((StringStat*) x1)).adress);
    // printf("y after swap = %s", (*((StringStat*) y1)).adress);
    // printf("--------------- end swap ---------------\n");
    // getchar();
}

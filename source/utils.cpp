#include <string.h>

#include "utils.h"

static const int CR_TARGET   = '\r';
static const int NULL_TARGET = '\0';


int get_strings_number(char* input_buffer)
{
    int strings_number = 0;
    char* last_str_ptr = input_buffer;

    while ((last_str_ptr = strchr(last_str_ptr, CR_TARGET)) != NULL)
    {
        *last_str_ptr++ = '\n'; *last_str_ptr++ = '\0';
        strings_number++;
    }

    return strings_number;
}


void read_strings(struct DiffSortedText* text, char* input_buffer, int input_buffer_length)
{
    int read_strings_number = 0;
    char* const max_buffer_adress = input_buffer + input_buffer_length - 1;
    char* last_str_ptr = input_buffer;
    char* new_str_ptr = input_buffer;

    while(true)
    {
        new_str_ptr = strchr(last_str_ptr, NULL_TARGET) + 1;

        text->no_sort[read_strings_number] = text->dir_sort[read_strings_number] = \
            text->rev_sort[read_strings_number] = {last_str_ptr, (int) (new_str_ptr - last_str_ptr)};

        last_str_ptr = new_str_ptr;
        read_strings_number++;

        if (new_str_ptr == max_buffer_adress)
            break;
    }
}


void swap(void* x, void* y, size_t var_size)
{
    typedef unsigned long long tmp_type1;
    tmp_type1 tmp1 = 0;
    while (var_size >= sizeof(tmp1))
    {
        tmp1 = *((tmp_type1*) x);
        *((tmp_type1*) x) = *((tmp_type1*) y);
        *((tmp_type1*) y) = tmp1;

        x = ((tmp_type1*) x) + 1; y = ((tmp_type1*) y) + 1;

        var_size -= sizeof(tmp_type1);
    }

    typedef char tmp_type2;
    tmp_type2 tmp2 = 0;
    for (size_t i = 0; i < var_size; i++)
    {
        tmp2 = *((tmp_type2*) x + i);
        *((tmp_type2*) x + i) = *((tmp_type2*) y + i);
        *((tmp_type2*) y + i) = tmp2;
    }
}

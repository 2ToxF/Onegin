#include <stdlib.h>

#include "input_output.h"
#include "sorters.h"
#include "utils.h"

CodeError run_program();


int main()
{
    CodeError code_err = run_program();
    print_code_error(code_err);
    return code_err;
}


CodeError run_program()
{
    CodeError code_err = NO_ERROR;

    char* input_buffer = NULL;
    int input_buffer_length = 0;
    if ((code_err = fopen_and_read(&input_buffer, &input_buffer_length)) != NO_ERROR)
        return code_err;

    int strings_number = get_strings_number(input_buffer);
    struct DiffSortedText text = {(char**)              calloc((size_t) strings_number, sizeof(StringStat)),
                                  (struct StringStat*)  calloc((size_t) strings_number, sizeof(StringStat)),
                                  (char**)              calloc((size_t) strings_number, sizeof(StringStat))};

    read_strings(&text, input_buffer, input_buffer_length);
    sort_onegin(&text, strings_number);

    if ((code_err = fprint_result(&text, strings_number)) != NO_ERROR)
        return code_err;

    FREE(text.dir_sort)
    FREE(text.rev_sort)
    FREE(text.no_sort)

    return code_err;
}

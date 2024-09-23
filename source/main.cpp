#include <stdlib.h>

#include "cmd_processing.h"
#include "input_output.h"
#include "sorters.h"
#include "utils.h"

CodeError run_program(int argc, char* argv[]);


int main(int argc, char* argv[])
{
    CodeError code_err = run_program(argc, argv);
    print_code_error(code_err);
    return code_err;
}


CodeError run_program(int argc, char* argv[])
{
    CodeError code_err = NO_ERROR;
    char input_file_name[50] = "onegin.txt", output_file_name[50] = "result.txt", sort_type[15] = "all";

    if ((code_err = cmd_read(argc, argv, input_file_name, output_file_name, sort_type)) != NO_ERROR)
        return code_err;

    char* input_buffer = NULL;
    int input_buffer_length = 0;
    if ((code_err = my_fread(&input_buffer, &input_buffer_length, input_file_name)) != NO_ERROR)
        return code_err;

    int strings_number = get_strings_number(input_buffer);
    struct DiffSortedText text = {(char**)              calloc((size_t) strings_number, sizeof(StringStat)),
                                  (struct StringStat*)  calloc((size_t) strings_number, sizeof(StringStat)),
                                  (char**)              calloc((size_t) strings_number, sizeof(StringStat))};

    read_strings(&text, input_buffer, input_buffer_length);
    if ((code_err = sort_onegin(&text, strings_number, sort_type)) != NO_ERROR)
        return code_err;

    if ((code_err = fprint_all_results(&text, strings_number, output_file_name, sort_type)) != NO_ERROR)
        return code_err;

    FREE(text.dir_sort)
    FREE(text.rev_sort)
    FREE(text.no_sort)

    return code_err;
}

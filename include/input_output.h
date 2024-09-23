#ifndef IO_H
#define IO_H

#include "utils.h"

CodeError my_fread(char** input_buffer, int* input_buffer_length, char* input_file_name);
CodeError fprint_all_results(const struct DiffSortedText* text, int strings_number,
                            char* output_file_name, char* sort_type);
void print_code_error(CodeError code_err);
void print_help();
void print_prank();

#endif

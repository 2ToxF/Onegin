#ifndef IO_H
#define IO_H

#include "utils.h"

CodeError my_fread(char** input_buffer, int* input_buffer_length);
CodeError fprint_result(const struct DiffSortedText* text, int strings_number);
void print_code_error(CodeError code_err);

#endif

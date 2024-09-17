#ifndef IO_H
#define IO_H

#include "utils.h"

enum CodeError
{
    NO_ERROR,
    FILLING_STAT_ERROR,
    FILE_NOT_OPENED_ERROR,
    WRONG_BUF_SIZE_ERROR,
};

CodeError fopen_and_read(char** input_buffer, int* input_buffer_length);
CodeError fprint_result(const struct DiffSortedText* text, int strings_number);

#endif

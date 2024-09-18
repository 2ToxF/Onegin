#include <stdio.h>
#include <stdlib.h>
#include <sys\stat.h>

#include "io.h"

#define RED_CMD_COLOR "\033[0;31m"
#define GRN_CMD_COLOR "\033[0;32m"
#define WHT_CMD_COLOR "\033[0;37m"

static const char* const FILE_INPUT_NAME  = "onegin.txt";
static const char* const FILE_RESULT_NAME = "result.txt";
static const int NUM_OF_ACTIONS_PER_CHAR = 1;


CodeError fopen_and_read(char** input_buffer, int* input_buffer_length)
{
    struct stat input_file_stat = {};
    if (stat(FILE_INPUT_NAME, &input_file_stat) != 0)
    {
        printf("ERROR: FILLING \"STRUCT STAT\" WAS FAILED\n");
        return FILLING_STAT_ERROR;
    }
    *input_buffer_length = input_file_stat.st_size + 1;

    FILE* input_fptr = fopen(FILE_INPUT_NAME, "rb");
    if (input_fptr == NULL)
    {
        printf("ERROR: FILE NOT OPENED\n");
        return FILE_NOT_OPENED_ERROR;
    }

    *input_buffer = (char*) calloc(*input_buffer_length, sizeof(char));
    long long unsigned int success_read_string_length = fread(*input_buffer, NUM_OF_ACTIONS_PER_CHAR,
                                                               input_file_stat.st_size, input_fptr);
    if (success_read_string_length != (long long unsigned int) input_file_stat.st_size)
    {
        printf("ERROR: WRONG SIZE OF INPUT BUFFER\n"
               "read: %llu; expected: %ld\n",
               success_read_string_length, input_file_stat.st_size);
        return WRONG_BUF_SIZE_ERROR;
    }

    FCLOSE(input_fptr)
    return NO_ERROR;
}


CodeError fprint_result(const struct DiffSortedText* text, int strings_number)
{
    FILE* result_fptr = fopen(FILE_RESULT_NAME, "wb");
    if (result_fptr == NULL)
        return FILE_NOT_OPENED_ERROR;

    fprintf(result_fptr, "-------------------------- directly sorted text --------------------------\n\n");
    for (int i = 0; i < strings_number; i++)
        fprintf(result_fptr, "%s", text->dir_sort[i]);

    fprintf(result_fptr, "\n-------------------------- reversed sorted text --------------------------\n\n");
    for (int i = 0; i < strings_number; i++)
        fprintf(result_fptr, "%s", text->rev_sort[i].adress);

    fprintf(result_fptr, "\n---------------------------- not sorted text ----------------------------\n\n");
    for (int i = 0; i < strings_number; i++)
        fprintf(result_fptr, "%s", text->no_sort[i]);

    FCLOSE(result_fptr)
    return NO_ERROR;
}


void print_code_error(CodeError code_err)
{
    switch (code_err)
    {
        case NO_ERROR:
            printf(GRN_CMD_COLOR "Code was completed without errors" WHT_CMD_COLOR "\n");
            break;

        case FILLING_STAT_ERROR:
            printf(RED_CMD_COLOR "ERROR: FILLING_STAT_ERROR" WHT_CMD_COLOR "\n");
            break;

        case FILE_NOT_OPENED_ERROR:
            printf(RED_CMD_COLOR "ERROR: FILE_NOT_OPENED_ERROR" WHT_CMD_COLOR "\n");
            break;

        case WRONG_BUF_SIZE_ERROR:
            printf(RED_CMD_COLOR "ERROR: WRONG_BUF_SIZE_ERROR" WHT_CMD_COLOR "\n");
            break;

        default:
            printf(RED_CMD_COLOR "UNKNOWN ERROR" WHT_CMD_COLOR "\n");
            break;
    }
}

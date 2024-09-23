#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd_processing.h"
#include "input_output.h"
#include "sorters.h"

#define RED_CMD_COLOR "\033[0;31m"
#define GRN_CMD_COLOR "\033[0;32m"
#define BLU_CMD_COLOR "\033[0;34m"
#define WHT_CMD_COLOR "\033[0;37m"

static const int NUM_OF_ACTIONS_PER_CHAR = 1;


CodeError my_fread(char** input_buffer, int* input_buffer_length, char* input_file_name)
{
    CodeError code_err = NO_ERROR;

    FILE* input_fptr = fopen(input_file_name, "rb");
    if (input_fptr == NULL)
        return FILE_NOT_OPENED_ERROR;

    if ((code_err = fsize(input_file_name, input_buffer_length)) != NO_ERROR)
        return code_err;

    *input_buffer = (char*) calloc(*input_buffer_length, sizeof(char));
    long long unsigned int success_read_string_length = fread(*input_buffer, NUM_OF_ACTIONS_PER_CHAR,
                                                              *input_buffer_length - 1, input_fptr);
    if (success_read_string_length != (long long unsigned int) (*input_buffer_length - 1))
        return WRONG_BUF_SIZE_ERROR;

    FCLOSE(input_fptr)
    return code_err;
}


CodeError fprint_all_results(const struct DiffSortedText* text, int strings_number,
                             char* output_file_name, char* sort_type)
{
    FILE* result_fptr = fopen(output_file_name, "wb");
    if (result_fptr == NULL)
        return FILE_NOT_OPENED_ERROR;

    if (strcmp(sort_type, SORT_ALL_CMD) == 0)
    {
        fprintf(result_fptr, "-------------------------- directly sorted text --------------------------\n\n");
        for (int i = 0; i < strings_number; i++)
            fprintf(result_fptr, "%s", text->dir_sort[i]);

        fprintf(result_fptr, "\n-------------------------- reversed sorted text --------------------------\n\n");
        for (int i = 0; i < strings_number; i++)
            fprintf(result_fptr, "%s", text->rev_sort[i].adress);

        fprintf(result_fptr, "\n---------------------------- not sorted text ----------------------------\n\n");
        for (int i = 0; i < strings_number; i++)
            fprintf(result_fptr, "%s", text->no_sort[i]);
    }

    else if (strcmp(sort_type, SORT_DIR_CMD) == 0)
    {
        fprintf(result_fptr, "-------------------------- directly sorted text --------------------------\n\n");
        for (int i = 0; i < strings_number; i++)
            fprintf(result_fptr, "%s", text->dir_sort[i]);

        fprintf(result_fptr, "\n---------------------------- not sorted text ----------------------------\n\n");
        for (int i = 0; i < strings_number; i++)
            fprintf(result_fptr, "%s", text->no_sort[i]);
    }

    else if (strcmp(sort_type, SORT_REV_CMD) == 0)
    {
        fprintf(result_fptr, "-------------------------- reversed sorted text --------------------------\n\n");
        for (int i = 0; i < strings_number; i++)
            fprintf(result_fptr, "%s", text->rev_sort[i].adress);

        fprintf(result_fptr, "\n---------------------------- not sorted text ----------------------------\n\n");
        for (int i = 0; i < strings_number; i++)
            fprintf(result_fptr, "%s", text->no_sort[i]);
    }

    FCLOSE(result_fptr)
    return NO_ERROR;
}


void print_code_error(CodeError code_err)
{
    #define ERR_DESCR_(error, code) case error##_ERROR:                                                     \
                                        printf(RED_CMD_COLOR "ERROR: " #error "_ERROR" WHT_CMD_COLOR "\n"); \
                                        {code}                                                              \
                                        break;                                                              \

    switch (code_err)
    {
        case NO_ERROR:
            printf(GRN_CMD_COLOR "Code was completed without errors" WHT_CMD_COLOR "\n");
            break;

        case CMD_HELP_NO_ERROR:
            printf(BLU_CMD_COLOR "Hint was printed succesfully" WHT_CMD_COLOR "\n");
            break;

        case CMD_PRANK_NO_ERROR:
            printf(BLU_CMD_COLOR "Prank was printed succesfully" WHT_CMD_COLOR "\n");
            break;

        ERR_DESCR_(UNKNOWN_OPTION, {print_help();})
        ERR_DESCR_(FILLING_STAT, {})
        ERR_DESCR_(FILE_NOT_OPENED, {})
        ERR_DESCR_(WRONG_BUF_SIZE, {})

        default:
            printf(RED_CMD_COLOR "UNKNOWN ERROR" WHT_CMD_COLOR "\n");
            break;
    }

    #undef ERR_DESCR_
}


void print_help()
{
    printf("Usage: ./QuadSolver.exe [options]\n"
           "Options:\n"
           "  %-16s Sets input file name (by default <file> = \"onegin.txt\")\n"
           "  %-16s Sets output file name (by default <file> = \"result.txt\")\n"
           "  %-16s Sets type of sorting: 1) <type> = \"dir\" for direct sorting\n"
           "                                         2) <type> = \"rev\" for reverse sorting\n"
           "                                         3) \"all\" for both (is set by default)\n"
           "  %-16s Prints hint with program options\n"
           "  %-16s DOES SOME PRANK\n\n",
           INPUT_FILE_CMD "=<file>",
           OUTPUT_FILE_CMD "=<file>",
           SORT_TYPE_CMD "=<type>",
           HELP_FULL_CMD ", " HELP_SHORT_CMD,
           PRANK_FULL_CMD ", " PRANK_SHORT_CMD);
    printf("         />    >\n"
           "         |  _  _|\n"
           "       _/`= _x =|\n"
           "      /        |\n"
           "   __|   \\    /\n"
           " /  _|    | | |\n"
           " | (  \\___\\_)_)\n"
           " \\__)\n\n");
}


void print_prank()
{
    printf(RED_CMD_COLOR "YOU ARE STUPID, UGLY IDIOT" WHT_CMD_COLOR "\n\n");
}

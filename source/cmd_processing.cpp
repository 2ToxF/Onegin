#include <stdio.h>
#include <string.h>

#include "cmd_processing.h"
#include "input_output.h"

CodeError cmd_read(int argc, char* argv[], char* input_file_name, char* output_file_name, char* sort_type)
{
    for (int i = 1; i < argc; i++)
    {
        char option_part1[25] = {}, option_part2[25] = {}, option[25] = {};

        if (sscanf(argv[i], "%[^=]=%s", option_part1, option_part2) == 2)
        {
            if (strcmp(option_part1, INPUT_FILE_CMD) == 0)
                strcpy(input_file_name, option_part2);
            else if (strcmp(option_part1, OUTPUT_FILE_CMD) == 0)
                strcpy(output_file_name, option_part2);
            else if (strcmp(option_part1, SORT_TYPE_CMD) == 0)
                strcpy(sort_type, option_part2);
            else
                return UNKNOWN_OPTION_ERROR;
        }

        else
        {
            sscanf(argv[i], "%s", option);

            if (strcmp(option, HELP_FULL_CMD) == 0 || strcmp(option, HELP_SHORT_CMD) == 0)
            {
                print_help();
                return CMD_HELP_NO_ERROR;
            }
            else if (strcmp(option, PRANK_FULL_CMD) == 0 || strcmp(option, PRANK_SHORT_CMD) == 0)
            {
                print_prank();
                return CMD_PRANK_NO_ERROR;
            }
            else
                return UNKNOWN_OPTION_ERROR;
        }
    }

    return NO_ERROR;
}

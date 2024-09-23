#ifndef CMD_PROCESSING_H
#define CMD_PROCESSING_H

#include "utils.h"

#define INPUT_FILE_CMD  "--input"
#define OUTPUT_FILE_CMD "--output"
#define SORT_TYPE_CMD   "--sort"
#define HELP_FULL_CMD   "--help"
#define HELP_SHORT_CMD  "-h"
#define PRANK_FULL_CMD  "--prank"
#define PRANK_SHORT_CMD "-p"

CodeError cmd_read(int argc, char* argv[], char* input_file_name, char* output_file_name, char* sort_type);

#endif

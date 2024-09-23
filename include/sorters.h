#ifndef SORTERS_H
#define SORTERS_H

#include "utils.h"

const char SORT_ALL_CMD[] = "all";
const char SORT_DIR_CMD[] = "dir";
const char SORT_REV_CMD[] = "rev";

CodeError sort_onegin(struct DiffSortedText* text, int strings_number, char* sort_type);

#endif

#include <assert.h>
#include <ctype.h>

#include "comparators.h"
#include "utils.h"


int compare_direct(void* void_str1, void* void_str2)
{
    assert(void_str1 != NULL);
    assert(void_str2 != NULL);

    char* str1 = *((char**) void_str1);
    char* str2 = *((char**) void_str2);
    int idx1 = 0, idx2 = 0;

    while (str1[idx1] != '\0' && str2[idx2] != '\0')
    {
        while (isalpha(str1[idx1]) == 0 && str1[idx1] != '\0')
            idx1++;
        while (isalpha(str2[idx2]) == 0 && str2[idx2] != '\0')
            idx2++;

        if (str1[idx1] == '\0' || str2[idx2] == '\0')
            break;

        if (toupper(str1[idx1]) != toupper(str2[idx2]))
            return toupper(str1[idx1]) - toupper(str2[idx2]);

        idx1++; idx2++;
    }

    return idx2 - idx1;
}


int compare_reverse(void* void_strstat1, void* void_strstat2)
{
    assert(void_strstat1 != NULL);
    assert(void_strstat2 != NULL);

    struct StringStat strstat1 = *((StringStat*) void_strstat1);
    struct StringStat strstat2 = *((StringStat*) void_strstat2);
    int idx1 = strstat1.len - 1, idx2 = strstat2.len - 1;

    while (idx1 >= 0 && idx2 >= 0)
    {
        while (idx1 >= 0 && isalpha(strstat1.adress[idx1]) == 0)
            idx1--;
        while (idx2 >= 0 && isalpha(strstat2.adress[idx2]) == 0)
            idx2--;

        if (idx1 < 0 || idx2 < 0)
            break;

        if (toupper(strstat1.adress[idx1]) !=
            toupper(strstat2.adress[idx2]))
            {
            return toupper(strstat1.adress[idx1]) -
                   toupper(strstat2.adress[idx2]);
            }

        idx1--; idx2--;
    }

    return idx1 - idx2;
}

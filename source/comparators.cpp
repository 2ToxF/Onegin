#include <assert.h>
#include <ctype.h>

#include "comparators.h"
#include "utils.h"


int compare_direct(void* void_str1, void* void_str2, size_t)
{
    assert(void_str1 != NULL);
    assert(void_str2 != NULL);

    char* str1 = *((char**) void_str1);
    char* str2 = *((char**) void_str2);
    int s1ind = 0, s2ind = 0;

    while (str1[s1ind] != '\0' && str2[s2ind] != '\0')
    {
        while (isalpha(str1[s1ind]) == 0 && str1[s1ind] != '\0')
            s1ind++;
        while (isalpha(str2[s2ind]) == 0 && str2[s2ind] != '\0')
            s2ind++;

        if (str1[s1ind] == '\0' || str2[s2ind] == '\0')
            break;

        if (toupper(str1[s1ind]) != toupper(str2[s2ind]))
            return toupper(str1[s1ind]) - toupper(str2[s2ind]);

        s1ind++; s2ind++;
    }

    return s2ind - s1ind;
}


int compare_reverse(void* void_strstat1, void* void_strstat2, size_t)
{
    assert(void_strstat1 != NULL);
    assert(void_strstat2 != NULL);

    struct StringStat strstat1 = *((StringStat*) void_strstat1);
    struct StringStat strstat2 = *((StringStat*) void_strstat2);
    int s1ind = strstat1.len - 1, s2ind = strstat2.len - 1;

    while (s1ind >= 0 && s2ind >= 0)
    {
        while (s1ind >= 0 && isalpha(strstat1.adress[s1ind]) == 0)
            s1ind--;
        while (s2ind >= 0 && isalpha(strstat2.adress[s2ind]) == 0)
            s2ind--;

        if (s1ind < 0 || s2ind < 0)
            break;

        if (toupper(strstat1.adress[s1ind]) != toupper(strstat2.adress[s2ind]))
            return toupper(strstat1.adress[s1ind]) - toupper(strstat2.adress[s2ind]);

        s1ind--; s2ind--;
    }

    return s1ind - s2ind;
}

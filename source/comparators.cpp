#include <assert.h>
#include <ctype.h>

#include "comparators.h"
#include "utils.h"


int compare_direct(void* void_strstat1, void* void_strstat2, size_t)
{
    assert(void_strstat1 != NULL);
    assert(void_strstat2 != NULL);

    struct StringStat strstat1 = *((StringStat*) void_strstat1);
    struct StringStat strstat2 = *((StringStat*) void_strstat2);
    int s1ind = 0, s2ind = 0;

    while (s1ind < strstat1.len && s2ind < strstat2.len)
    {
        while (isalpha(strstat1.adress[s1ind]) == 0)
            s1ind++;
        while (isalpha(strstat2.adress[s2ind]) == 0)
            s2ind++;

        if (strstat1.adress[s1ind] == 0 || strstat2.adress[s2ind] == 0)
            break;

        if (toupper(strstat1.adress[s1ind]) != toupper(strstat2.adress[s2ind]))
            return toupper(strstat1.adress[s1ind]) - toupper(strstat2.adress[s2ind]);

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
        while (isalpha(strstat1.adress[s1ind]) == 0)
            s1ind--;
        while (isalpha(strstat2.adress[s2ind]) == 0)
            s2ind--;

        if (strstat1.adress[s1ind] == 0 || strstat2.adress[s2ind] == 0)
            break;

        if (toupper(strstat1.adress[s1ind]) != toupper(strstat2.adress[s2ind]))
            return toupper(strstat1.adress[s1ind]) - toupper(strstat2.adress[s2ind]);

        s1ind--; s2ind--;
    }

    return s1ind - s2ind;
}

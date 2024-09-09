#include <ctype.h>
#include <stdio.h>

const int MAX_STRINGS_LEN = 50;

int compare_direct(char* s1, char* s2);
int compare_reverse(char* s1, char* s2);
int partition (char* arr[], int low, int high, int (*compare_func)(char*, char*));
void quick_sort(char* arr[], int low, int high, int (*compare_func)(char*, char*));
void swap(char** x, char** y);

int main()
{
    const char* const FILE_ONEGIN_NAME = "onegin.txt";
    const char* const FILE_RESULT_NAME = "result.txt";
    const int MAX_STRINGS_NUM = 5350;

    FILE* onegin_fptr = fopen(FILE_ONEGIN_NAME, "r");
    char strings[MAX_STRINGS_NUM][MAX_STRINGS_LEN] = {};
    char* strptrs_direct_sw[MAX_STRINGS_NUM] = {};
    char* strptrs_reverse_sw[MAX_STRINGS_NUM] = {};

    int real_strings_number = 0;
    for (int i = 0; feof(onegin_fptr) == 0; i++)
    {
        fgets(strings[i], MAX_STRINGS_LEN, onegin_fptr);
        strptrs_direct_sw[i] = strings[i];
        strptrs_reverse_sw[i] = strings[i];
        real_strings_number++;
    }
    real_strings_number--;

    const int START_OF_MAS = 0, END_OF_MAS = real_strings_number - 1;
    quick_sort(strptrs_direct_sw, START_OF_MAS, END_OF_MAS, compare_direct);
    quick_sort(strptrs_reverse_sw, START_OF_MAS, END_OF_MAS, compare_reverse);

    FILE* result_fptr = fopen(FILE_RESULT_NAME, "w");

    for (int i = 0; i < real_strings_number; i++)
        fprintf(result_fptr, "%s", strptrs_direct_sw[i]);
    fprintf(result_fptr, "\n\n-----------------------------------------------------------------------\n\n\n");

    for (int i = 0; i < real_strings_number; i++)
        fprintf(result_fptr, "%s", strptrs_reverse_sw[i]);
    fprintf(result_fptr, "\n\n-----------------------------------------------------------------------\n\n\n");

    for (int i = 0; i < real_strings_number; i++)
        fprintf(result_fptr, "%s", strings[i]);

    fclose(onegin_fptr); onegin_fptr = NULL;
    fclose(result_fptr); result_fptr = NULL;
    return 0;
}


int compare_direct(char* s1, char* s2)
{
    int s1ind = 0, s2ind = 0;
    while (s1ind < MAX_STRINGS_LEN && s2ind < MAX_STRINGS_LEN)
    {
        if (isalpha(s1[s1ind]) == 0)
        {
            s1ind++;
            continue;
        }
        if (isalpha(s2[s2ind]) == 0)
        {
            s2ind++;
            continue;
        }

        if (toupper(s1[s1ind]) != toupper(s2[s2ind]))
            return toupper(s1[s1ind]) - toupper(s2[s2ind]);
        s1ind++; s2ind++;
    }

    if (s1ind != s2ind)
        return s2ind - s1ind;
    return 0;
}


int compare_reverse(char* s1, char* s2)
{
    int s1ind = MAX_STRINGS_LEN-1, s2ind = MAX_STRINGS_LEN-1;
    while (s1ind >= 0 && s2ind >= 0)
    {
        if (isalpha(s1[s1ind]) == 0)
        {
            s1ind--;
            continue;
        }
        if (isalpha(s2[s2ind]) == 0)
        {
            s2ind--;
            continue;
        }

        if (toupper(s1[s1ind]) != toupper(s2[s2ind]))
            return toupper(s1[s1ind]) - toupper(s2[s2ind]);
        s1ind--; s2ind--;
    }

    if (s1ind != s2ind)
        return s2ind - s1ind;
    return 0;
}


int partition(char* arr[], int low, int high, int (*compare_func)(char*, char*))
{
    // Initialize pivot to be the first element
    char* p = arr[low];
    int i = low;
    int j = high;

    while (i < j)
    {
        // Find the first element greater than
        // the pivot (from starting)
        while (compare_func(arr[i], p) <= 0 && i <= high - 1)
            i++;

        // Find the first element smaller than
        // the pivot (from last)
        while (compare_func(arr[j], p) > 0 && j >= low + 1)
            j--;

        if (i < j)
            swap(&arr[i], &arr[j]);
    }
    swap(&arr[low], &arr[j]);

    return j;
}


void quick_sort(char* arr[], int low, int high, int (*compare_func)(char*, char*))
{
    if (low < high)
    {
        // call partition function to find Partition Index
        int pi = partition(arr, low, high, compare_func);

        // Recursively call quick_sort() for left and right
        // half based on Partition Index
        quick_sort(arr, low, pi - 1, compare_func);
        quick_sort(arr, pi + 1, high, compare_func);
    }
}


void swap(char** x, char** y)
{
    char* tmp = *x;
    *x = *y;
    *y = tmp;
    return;
}

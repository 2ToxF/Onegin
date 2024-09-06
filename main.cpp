#include <stdio.h>

const int MAX_STRINGS_LEN = 50;

int compare_direct(char* s1, char* s2);
int partition (char* arr[], int low, int high);
void quick_sort(char* arr[], int low, int high);
void swap(char** x, char** y);

int main()
{
    const char* const FILE_NAME = "text.txt";
    const int MAX_STRINGS_NUM = 4000;

    FILE* fptr = fopen(FILE_NAME, "r");
    char strings[MAX_STRINGS_NUM][MAX_STRINGS_LEN] = {};
    char* strptrs[MAX_STRINGS_NUM] = {};

    int real_strings_number = 0;
    for (int i = 0; feof(fptr) == 0; i++)
    {
        fgets(strings[i], MAX_STRINGS_LEN, fptr);
        strptrs[i] = strings[i];
        real_strings_number++;
    }

    const int START_OF_MAS = 0, END_OF_MAS = real_strings_number - 1;
    quick_sort(strptrs, START_OF_MAS, END_OF_MAS);

    for (int i = 0; i < real_strings_number; i++)
        printf("%s", strings[i]);

    fclose(fptr); fptr = NULL;
    return 0;
}


int compare_direct(char* s1, char* s2)
{
    int s1ind = 0, s2ind = 0;
    while (s1ind < MAX_STRINGS_LEN && s2ind < MAX_STRINGS_LEN)
    {
        if ((('A' <= s1[s1ind] && s1[s1ind] <= 'Z') || ('a' <= s1[s1ind] && s1[s1ind] <= 'z')) == 0)
        {
            s1ind++;
            continue;
        }
        if ((('A' <= s2[s2ind] && s2[s2ind] <= 'Z') || ('a' <= s2[s2ind] && s2[s2ind] <= 'z')) == 0)
        {
            s2ind++;
            continue;
        }

        if (s1[s1ind] != s2[s2ind])
            return s1[s1ind] - s2[s2ind];
        s1ind++; s2ind++;
    }

    if (s1ind != s2ind)
        return s2ind - s1ind;
    return 0;
}


int partition(char* arr[], int low, int high)
{
    // Initialize pivot to be the first element
    char* p = arr[low];
    int i = low;
    int j = high;

    while (i < j)
    {
        // Find the first element greater than
        // the pivot (from starting)
        while (compare_direct(arr[i], p) <= 0 && i <= high - 1)
            i++;

        // Find the first element smaller than
        // the pivot (from last)
        while (compare_direct(arr[j], p) > 0 && j >= low + 1)
            j--;

        if (i < j)
            swap(&arr[i], &arr[j]);
    }
    printf("pizdec");
    swap(&arr[low], &arr[j]);

    return j;
}


void quick_sort(char* arr[], int low, int high)
{
    if (low < high)
    {
        // call partition function to find Partition Index
        int pi = partition(arr, low, high);

        // Recursively call suick_sort() for left and right
        // half based on Partition Index
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}


void swap(char** x, char** y)
{
    char** tmp = x;
    x = y;
    y = tmp;
    return;
}

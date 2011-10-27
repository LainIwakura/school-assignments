/* Written by Zachary Easterbrook
 * Student ID: 103163420
 */

#include <stdio.h>
#include <string.h>

// declare our struct
struct WordStruct
{
    char Word[51];
    int length;
} WordList[25], temp;

// function prototypes
void TokenToArray(char []);
void PrintArray(int);
void WriteFile(int);
void BubbleSort(int, int);

// entry point
int main()
{
    char InputString[] = "the cat in the hat jumped over the lazy fox done";
    TokenToArray(InputString);

    return 0;
}

/* I decided to make a separate function for this
 * It tokenizes a string, takes an array (the string)
 * as input.
 * most of our work happens here.
 */
void TokenToArray(char tokens[])
{
    int i = 0;
    char *result = NULL;
    result = strtok(tokens," ");
    while(strcmp(result,"done") != 0)
    {
        strcpy(WordList[i].Word, result);
        WordList[i].length = strlen(result);
        result = strtok(NULL," ");
        ++i;
    }
    PrintArray(i);
    printf("-----SORT-------\n");
    BubbleSort(0,i);
    PrintArray(i);
    WriteFile(i);
}

/* function to print the array
 * takes array length as input
 * out puts the word, and length of the word.
 */
void PrintArray(int arr_length)
{
    int i = 0;
    for(; i < arr_length; ++i)
        printf("%s %d\n", WordList[i].Word, WordList[i].length);
}

/* function to write the array to a file.
 * takes the size of the array as input
 * outputs the data to a file.
 */
void WriteFile(int size)
{
    int i = 0;
    FILE *file;
    if((file = fopen("wlist.txt", "w")) == NULL)
        printf("Error opening file!\n");
    else
    {
        fprintf(file, "%s", "word|length\n");
        fprintf(file, "%s", "-----------\n");
        for(; i < size; ++i)
            fprintf(file, "%s %d\n", WordList[i].Word, WordList[i].length);
    }
}

/* Our new version of bubble sort, it's recursive,
 * uses a pivot point, and sorts two halves of a list.
 * You might say it's pretty..."quick"
 */
void BubbleSort(int lower, int upper)
{
    // our base case
    if(upper - lower < 2)
        return;
    int k = lower;
    int i, j;
    // Putting the pivot in sorted position, pivot is last element.
    for(i = lower; i < upper; ++i)
    {   
        if(strcmp(WordList[i].Word,WordList[upper - 1].Word) < 0)
            ++k; // Number of elements less than the pivot.
    }   
    
    // This is where we actually switch our pivot to the proper spot
    temp = WordList[k];
    WordList[k] = WordList[upper - 1]; 
    WordList[upper - 1] = temp;

    // The first for loop puts everything lower
    // than the pivot on the right side
    for(j = lower; j < k; ++j)
    {   
        if(strcmp(WordList[j].Word,WordList[k].Word) >= 0)
        {   
            // put everything larger on the
            // left side
            for(i = k; i < upper; ++i)
            {   
               if(strcmp(WordList[k].Word,WordList[i].Word) > 0)
               {   
                   temp = WordList[i];
                   WordList[i] = WordList[j]; 
                   WordList[j] = temp;
                   break;
               }   
            }   
        }   
    }   
    // now sort our halves.
    BubbleSort(lower, k); 
    BubbleSort(k+1, upper);
}

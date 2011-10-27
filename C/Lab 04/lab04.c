/* Written by: Zachary Easterbrook
 * Student ID: 103163420
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function prototypes
// Reverse reverse!
void Reverse(char *);
void RecursiveReverse(char *, int, int);
void ParseSentence(char *);
void BubbleSort(char *[], int, int);

int main()
{
    // Declare our buffers
    // First is equivalent to the second.
    char Buffer1[] = {'t','h','i','s',' ','t','h','e',' ','f','i','r','s','t',' ','b','u','f','f','e','r','.','\0'};
    char Buffer2[] = "This is the second buffer";
    char Buffer3[80];
    int length; // hold the length of our third buffer

    // scanf("%s", &Buffer3); This will not accept whitespace, use fgets();
    printf("Enter your string, up to 80 characters.\n");
    fgets(Buffer3, 80, stdin);  // fgets is better than scanf and gets
    length = strlen(Buffer3) - 1;
    printf("%s\n", Buffer1);    // print out the first buffer    
    printf("%s\n", Buffer2);    
    printf("you entered: %s\n", Buffer3);    
    char *pBuffer = Buffer3;    // pointer to the first element of the array
    do
    {
        printf("%c", *pBuffer); // print out the third buffer
        ++pBuffer;
    }
    while(*pBuffer != '\0');
    // first function
    printf("\nLocation of Buffer 3: %p", Buffer3);
    printf("\n----------CALL TO REVERSE---------");
    Reverse(Buffer3);
    printf("\nLocation of Buffer 3: %p", Buffer3);
    printf("%s\n", Buffer3);
    // first function recursively
    RecursiveReverse(Buffer3, 0, length);
    printf("%s\n", Buffer3);
    // third function
    ParseSentence(Buffer3);
}

/* Purpose is to reverse a given string
 * takes the String as input
 * reduces the string in memory
 */

void Reverse(char *String)
{
    int end = strlen(String) - 1;
    int i;
    for(i = 0; i < end; ++i, --end)
    {
        // XOR swap
        String[end] ^= String[i];
        String[i] ^= String[end];
        String[end] ^= String[i];
    }
}

/* Same as above, but recursive.
 * String as input and then reverses
 * it in memory
 */

void RecursiveReverse(char *String, int start, int end)
{
   if(start < end)
   {
        // Recursive XOR swap
        String[end] ^= String[start];
        String[start] ^= String[end];
        String[end] ^= String[start];
        RecursiveReverse(String, start + 1, end - 1);
   }
   else
       return;
}

/* tokenize our string based on the delimiters
 * takes a pointer to the string as input
 * sorts the words using a separate function, then prints them.
 */
void ParseSentence(char *String)
{
    int i = 0, j;
    char delims[] = {' ', '.', ',', '\n'};
    char *result = NULL;
    char *words[80];
    result = strtok(String,delims);
    // storing the tokens in an array with a do / while loop
    do
        words[i++] = result;
    while(result = strtok(NULL,delims));

    // sort the words and print them
    BubbleSort(words,0,i);
    for(j = 0; j < i; ++j)
        printf("%s\n", *(words + j));
}

/* Our "BubbleSort", we wrote it recursively...
 * ...because "BubbleSort" is recursive now.
 */
void BubbleSort(char *Words[], int lower, int upper)
{
    // base case
    if(upper - lower < 2)
        return;
    int k = lower;
    int i, j;
    for(i = lower; i < upper; ++i)
    {
        if(strcmp(Words[i],Words[upper - 1]) < 0)
            ++k;
    }
    char *temp = Words[k];
    Words[k] = Words[upper - 1];
    Words[upper - 1] = temp;

    for(j = lower; j < k; ++j)
    {
        if(strcmp(Words[j],Words[k]) > 0)
        {
            for(i = k; i < upper; ++i)
            {
               if(strcmp(Words[k],Words[i]) > 0)
               {
                   char *temp2 = Words[i];
                   Words[i] = Words[j];
                   Words[j] = temp2;
                   break;
               }
            }
        }
    }
    BubbleSort(Words, lower, k);
    BubbleSort(Words, k+1, upper);
}

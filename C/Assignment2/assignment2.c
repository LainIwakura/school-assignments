/* Written by: Zachary Easterbrook
 * Student ID: 103163420
 * Section 01
 * Assignment #2
 * Data: Feb. 16th 2011
 * Purpose: To uncompress a text file in a certain format
 */

// Include files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// the one function we'll need.
void ridWord(char [100][51], int, int);

int main()
{
    char Words[100][51];    // Hold our words. Maximum 100 words, 51 chars per word.
    char line_buffer[BUFSIZ];   // a line buffer
    int word = 0, character = 0;    // counters
    int buildingWord = 0;   // flag for building a word

    fgets(line_buffer, BUFSIZ, stdin); // read the line
    while(1)    // while true
    {
        // if the line length is greater than 0 and the first element is 0,
        // we're done.
        if(line_buffer[0] == '0') 
            break;
        // pointer to the first character
        char *letter = line_buffer;
        while(*letter != '\0')  // while it's not a null terminator
        {
            if(isalnum(*letter))    // if it's an alphanumeric character, we start building a word.
            {
                buildingWord = 1;
                Words[word][character] = *letter;
                if(isalpha(*letter))
                    printf("%c", Words[word][character]);   // print alphabetic characters
                ++character;
            }
            else    // this catches spaces and punctuation
            {
                int temp;
                Words[word][character + 1] = '\0';  // append a terminator character to indicate the end of a word.
                if(buildingWord == 1)
                {
                    if(sscanf(Words[word], "%d", &temp) == 1)   // scan for an integer, if we find one...
                    {
                        printf("%s",Words[word - temp]);    // print the word at the proper index
                        ridWord(Words, temp, word); // remove it from our stack.
                    }
                    else    // we didn't find an int, so we must just have a new word... ++ that index.
                        ++word;
                    buildingWord = 0;
                    character = 0;
                }
                printf("%c", *letter);  // prints spaces / punctuation
            }
            ++letter; // move our pointer
        }
        fgets(line_buffer, BUFSIZ, stdin); // read the next line
    }

    return 0;
}

// This function handles our stack of words, it takes the stack, position we
// want, and length of the word.
void ridWord(char Words[100][51], int position, int length)
{
    char temp[51];
    int i;
    // copy the word at the correct index into a temp variable
    strcpy(temp,Words[length - position]);
    // move ever item down one
    for(i = length - position; i < length; ++i)
        strcpy(Words[i],Words[i+1]);
    // copy the temp word back to the front of the stack.
    strcpy(Words[length - 1],temp);
}

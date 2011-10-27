/* Written by Zach Easterbrook
 * AKA: YukiNagato / LainIwakura
 * Student ID: 103163420
 *  
 * This program does a few things to a 2D array.
 * It'll populate it with zeros, or random numbers.
 * It also sorts the array using bubble sort.
 *
 * In addition to this, it can sort the array for a particular
 * value.
 *
 * It will also move all element one to the left.
 */

#include <stdio.h>   // printf(), scanf()
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()

// Our array dimensions
#define M 10
#define N 5

/* Helper functions
 * We have two additional functions here beyond the regular one, they are
 * ToArray and ToArray2, one converts a 2D array to 1D and the other
 * turns 1D into 2D.
 */

int Menu(void);
int ToArray(int [M][N], int [M * N]);
int ToArray2(int [M][N], int [M * N]);

// Our main functions
int Init(int [M][N]);
int PrintArray(int [M][N]);
int RandArray(int [M][N]);
int SortArray(int [M][N]);
int SearchArray(int [M][N], int);
int RotateLeft(int [M][N]);

// Function to take 2D array and make it 1D
int ToArray(int nums[M][N], int nums1[M * N])
{
    int x, y;

    for(x = 0; x < M; ++x)
    {   
        for(y = 0; y < N; ++y) 
            nums1[(x * N) + y] = nums[x][y];
    }

    return 1;
}

// Function to take 1D array and make it 2D
int ToArray2(int nums[M][N], int nums1[M * N])
{
    int x, y;

    for(x = 0; x < M; ++x)
    {
        for(y = 0; y < N; ++y)
            nums[x][y] = nums1[(x * N) + y];
    }

    return 1;
}

// Function to print the menu.
int Menu(void)
{
    printf("Welcome to lab 2! Select one of the following.\n"
           "1) Initialize the array with zeros\n"
           "2) Populate array with random values\n"
           "3) Sort the array (bubble sort)\n"
           "4) Search the array for a value\n"
           "5) Rotate each element one to the left\n"
           "6) Manually print the array\n"
           "7) Quit the program\n"
           "8) Print this menu\n"
           "9) Clear the screen\n");
    
    return 1;
}   

/* Start main */
int main()
{
    // Our variables for which function to choose.
    // choice can hold a bunch of junk and we scan
    // for an int
    char choice[BUFSIZ];
    int choice2;
    
    // Variables. First one is the array, second one is the value we search for
    int nums[M][N];
    int value;
    
    system("clear");
    Menu();
    do
    {
        printf("lab02> ");
        scanf("%s", choice);
        if(!sscanf(choice, "%d", &choice2)) // Using this, we force an integer input
            continue;
        /* Our switch case prints a message, executes the function, indicates 
         * success and then prints the array.
         */

	    switch(choice2)
        {
            case 1:
                printf("Initalizing array...\n");
                Init(nums);
                printf("Initalization successful.\n");
                PrintArray(nums);
                break;
            case 2:
                printf("Populating array with random values...\n");
                RandArray(nums);
                printf("Success. Now the array is lol sorandum xD\n");
                PrintArray(nums);
                break;
            case 3:
                printf("Sorting array...\n");
                SortArray(nums);
                printf("Array sorted!\n");
                PrintArray(nums);
                break;
            case 4:
                printf("Search for which value in the array?\n");
                scanf("%d", &value);
                printf("Searching array for value %d...\n", value);
                SearchArray(nums, value);
                break;
            case 5:
                printf("Rotating values to the left...\n");
                RotateArray(nums);
                printf("Values rotated.\n");
                break;
            case 6:
                PrintArray(nums);
                break;
            case 7:
                printf("Exiting.\n");
                break;
            case 8:
                printf("\n");
                Menu();
                break;
            case 9:
                system("clear");
                break;
        }
    }
    while(choice2 != 7);
        
    return 0;
}

/* This function takes an array and initalizes all the values to 
 * zero.
 */

int Init(int nums[M][N])
{
    int x, y;
    for(x = 0; x < M; ++x)
    {    
        for(y = 0; y < N; ++y)
            nums[x][y] = 0;
    }
    
    return 1;
}

/* This function takes the array as an input parameter and 
 * prints it all in an intuitive and easy to read way.
 */

int PrintArray(int nums[M][N])
{
    int x, y;
    
    printf("Currently the array is:\n");
    
    for(x = 0; x < M; ++x)
    {
        for(y = 0; y < N; ++y)
        {
            printf("%02d ", nums[x][y]);
        }
        printf("\n");
    }

    return 1;
}

/* This takes the array as input and randomizes each cell with a number
 * between 0-99. We use srand to ensure "true" randomization.
 */
int RandArray(int nums[M][N])
{
    int x, y;
   
    srand(time(NULL));

    for(x = 0; x < M; ++x)
    {
        for(y = 0; y < N; ++y)
            nums[x][y] = rand() % 100;
    }

    return 1;
}

/* This program takes an array as input and sorts it using bubble sort.
 * It's not that hard.
 */

int SortArray(int nums[M][N])
{
    int nums1[M * N];
    int temp;
    int x, y, z;
    ToArray(nums, nums1);

    for(x = 0; x < (M * N); ++x)
    {
        for(y = 0; y < (M * N) - 1; ++y)
        {  
            if(nums1[y] > nums1[y + 1]) 
            {    
                temp = nums1[y + 1];
                nums1[y + 1] = nums1[y];
                nums1[y] = temp;
            }
        }      
    }

    ToArray2(nums, nums1);

    return 1;
}

/* This function takes an array as input as well as the value we are searching
 * it loops through the array until it finds a match, then it sets a found flag
 * to one. If that flag is on, the value was found.
 */

int SearchArray(int nums[M][N], int value)
{
    int x, y;
    int found = 0;
    
    for(x = 0; x < M; ++x)
    {
        for(y = 0; y < N; ++y)
            if(nums[x][y] == value)
                found = 1;
    }
    if(found != 0)
        printf("%d was found in our array.\n", value);
    else
        printf("%d was not found in our array.\n", value);

    return 1;
}

/* This function rotates the array, it takes the array as input.
 * It's only here for bonus marks lawlawlawl
 */

int RotateArray(int nums[M][N])
{
    int nums1[M * N];
    int x, y, first;
    ToArray(nums, nums1);
    first = nums1[0];

    for(x = 0; x < (M * N) - 1; ++x)
    {
            nums1[x] = nums1[x + 1] ;
    }
    nums1[(M * N) - 1] = first;

    ToArray2(nums, nums1);
    
    return 1;
}

#include <stdio.h>

// Enumerated constants
// This is safer than #define
// because #define is not type-safe
enum
{
    SORT_ASC = 0,
    SORT_DESC = 1,
    MAX = 20
};

// Our function prototypes
void Swap(int *, int *);
void BubbleSort(int [], int, int);
void PrintArray(int [], int);
int Triple(int *);

// -----START MAIN-----
int main()
{
    int iter = 0, iter2 = 0;
    int NumList[MAX];
    // Populate our array
    for(; iter < MAX; ++iter)
        *(NumList + iter) = (2 * (iter + 2)); 
    PrintArray(NumList, MAX);
    
    // Triple all elements
    for(; iter2 < MAX; ++iter2)
        Triple(NumList + iter2);
    PrintArray(NumList, MAX);

    BubbleSort(NumList, MAX, SORT_DESC);
    PrintArray(NumList, MAX);
    BubbleSort(NumList, MAX, SORT_ASC);
    PrintArray(NumList, MAX);
    return 0;
}

// Function to swap the value of two pointers
// takes two pointers are input
// no output, but it does swap their values.
void Swap(int *aPtr, int *bPtr)
{
    int aTemp, bTemp;
    aTemp = *aPtr;
    bTemp = *bPtr;

    *bPtr = aTemp;
    *aPtr = bTemp;
}

// Triple a given integer
// takes a pointer as input
// returns the value being pointed at * three
int Triple(int *cPtr)
{
    *cPtr = *cPtr * 3;

    return *cPtr;
}

// Function to print the array
// takes an array as input as well as the size
// outputs the array
void PrintArray(int Array[], int size)
{
    int iter = 0;
    for(; iter < size; ++iter)
        printf("%d ", *(Array + iter));
    printf("\n");
}

// Sorts the array
// Takes the array, array size, and sort order as input
// returns the sorted array
void BubbleSort(int Array[], int size, int sort_order)
{
    int x = 0, y;
    int count;
    do
    {
        count = 0;
        for(y = 0; y < size - 1; ++y)
        {
            // For ASC sort of DESC sort, depending on what is passed in
            switch(sort_order)
            {
                case 0:
                    if(*(Array + y) > *(Array + y + 1))
                    {
                        Swap((Array + y),(Array + y + 1));
                        ++count;
                    }
                    break;
                case 1:
                    if(*(Array + y) < *(Array + y + 1))
                    {
                        Swap((Array + y),(Array + y + 1));
                        ++count;
                    }
                    break;
            }
        }
    } while(count != 0);        
}

/* This program was written by Zachary Easterbook
 * Student ID: 103163420
 * Date: Jan-26-2011
 *
 * This is programmed using a brute-force solution since the input constraints
 * are fairly light.
 *
 * The only trouble I had was calculating the number of combinations, when this
 * is equal to 20 a long long is necessary to calculate the factorial. Having
 * realized this, I would like to write a different solution- but not right now
 *
 * I also would like to say that I understand some of the design here could be
 * better, I'm not sure I like the idea of chaining my functions together
 * instead of calling them all in main - but whatever. It's not too messy, and
 * it does work.
 *
 * THIS PROGRAM WAS TESTED IN THESE CONDITIONS:
 * || sol.cs.uwindsor.ca:
 * || cc: Sun C 5.8 Patch 121015-06 2007/10/03
 * || using sample data provided on assignment page
 *
 * || My Laptop:
 * || Arch Linux 2.6.36-ARCH
 * || gcc: version 4.5.2 (GCC)
 * || using sample data provided, and also using a custom set of input data
 * || that tested the maximum set of integers allowed.
 *
 */

// Standard input / output functions.
#include <stdio.h>
#include <stdlib.h>

/* Our function prototypes.
 * CombosFunc - Computes all of the possible combinations given our set of
 * n integers.
 * 
 * DifferencesFunc - Computes all the differences, finds the smallest ones
 * along with the correspond index. We are actually only interested in the
 * index, so only this value is permanently stored. (The difference value is
 * used in calculations, but not needed otherwise).
 *
 * PrintResults - As it name suggests, this function prints results.
 * 
 * Fac - Simple one line program to compute a factorial of a number.
 *
 * One note, through the whole program our functions take a last argument-
 * "total" or "total_set" this is a running count of how many cases we are
 * going through so we can display the correct iteration when we print the
 * data.
 *
 */

int CombosFunc(int [], int [], long long, int, int);
int DifferencesFunc(int [], int [], long long, int, int); 
int PrintResults(int [], int [], int [], int, int);
long long Fac(long long);

int main()
{
    long long num1;                 // This is long long so we can use it in our factorial
    int num2, i, total_set = 0;     // i is just a counter, num2 is for the set M of queries, total_set has been explained.

    while(1)
    {
        scanf("%lld", &num1);
        if(num1 == 0) // This checks if the set of integers is 0, if it is we obviously are done.
            break;
        else if(num1 > 20 || num1 < 0) // Just a check to make sure we stay within our limits.
        {
            printf("Your data set isn't properly formatted. It will break the program.\n");
            break;
        }
        else
        {
            ++total_set;        // Increment total set each time we enter this else statement.
            int NumSet[num1];   // The set of integers has a size equal to the number scanned in
            for(i = 0; i < num1; ++i)
            {
                scanf("%d", &NumSet[i]);    // Go through and scan this set
            }
            scanf("%d", &num2);
            if(num2 > 4 || num2 < 1)    // Another data check.
            {
                printf("Your data set isn't properly formatted. It will break the program.\n");
                break;
            }
            int QuerySet[num2];     // query set has a size equal to the number scanned in.
            for(i = 0; i < num2; ++i)
            {
                scanf("%d", &QuerySet[i]);  // Go through and scan this set
            }
            
            /* This next function call takes all of the data we have now,
             * and it will twist and turn it until we get our closest sums.
             */

            CombosFunc(NumSet, QuerySet, num1, num2, total_set);
        }
    }

    return 0; // Tell the OS everything went just fine.
}

// This function was previously described in the prototype section.
int CombosFunc(int Nums[], int Queries[], long long length_nums, int length_queries, int total)
{
    // This is a formula for nCr (Combinations), we're using the factorial
    // formula but there are other methods.
    int num_combos = (Fac(length_nums) / (Fac(2) * Fac(length_nums - 2)));
    int Combos[num_combos]; // The length of our combinations array is the number we just computed.
    int i, x, iter = 0; // iter keeps track of TOTAL iterations and is NOT reset.
    for(i = 0; i < length_nums; ++i)
    {
        /* Given that x = i + 1, x will never equal i and we can
         * not have duplicate values
         */

        for(x = i + 1; x < length_nums; ++x, ++iter)
        {
            Combos[iter] = Nums[i] + Nums[x]; // Combos at position iter is equal to Num at i + Num at x
        }
    }
    
    // Now that we have the combos...we can computer all the differences with
    // relation to the queries and keep track of the lowest ones. This really
    // didn't need to be a separate function, but it is to keep things readable
    DifferencesFunc(Combos, Queries, iter, length_queries, total);
    return 1;
}

// This function was previously described in the prototype section.
int DifferencesFunc(int Combinations[], int Queries[], long long length_combos, int length_queries, int total)
{
    int ClosestNums[length_queries];
    int Indexes[length_queries];        // This array stores the index values of the Combinations array.
    int i, j, k, index;
    for(i = 0; i < length_queries; ++i)
    {
        // Set the minimum element to the first element
        // If this is wrong, we'll fix it later.
        ClosestNums[i] = Combinations[0];
        for(j = 0; j < length_combos; ++j)
        {   
            // If the absolute value of one of our combinations - the queried
            // number is less than our current minimum, that will be the new
            // minimum.
            if(abs(Combinations[j] - Queries[i]) > ClosestNums[i])
                continue;
            else
            {
                ClosestNums[i] = abs(Combinations[j] - Queries[i]);
                Indexes[i] = j; // Where we set the index.
            }
        }
    }

    // All the hard work is done! Time to print it.
    PrintResults(Indexes, Combinations, Queries, length_queries, total);
    return 1;
}

// This function was previously described in the prototype section.
int PrintResults(int MinIndex[], int Combinations[], int Queries[], int length_queries, int total)
{
    int i, index; // index is just a variable to hold the index position for our Combinations array.
    printf("Case %d:\n", total); // this total is the one that has been passed through the whole program.
    for(i = 0; i < length_queries; ++i)
    {
        index = MinIndex[i];    // This ensures that index is the minimum value
        printf("Closest sum to %d is %d.\n", Queries[i], Combinations[index]); 
    }

    return 1;
}

/* Just sittin' here computin' some factorials.
 * Can also be read as:
 * if(n == 1)
 *      return n;
 * else
 *      return Fac(n - 1) * n;
 */

long long Fac(long long n)
{
    return n == 1 ? n : Fac(n - 1) * n;
}

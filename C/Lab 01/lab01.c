/* Written by: Zachary Easterbrook
 * AKA: YukiNagato / LainIwakura
 * Student ID: 103163420
 * 
 * We've made a few maybe unconventional choices in this program
 * but they'll be explained as we come to them.
 */

/* We use stdarg.h so we can handle functions with a variable amount of
 * input. In this case, it's only the DataCheck function- and it will
 * only have at most four inputs, but we can't do this in an easier 
 * way.
 */

#include <stdio.h> 
#include <stdarg.h> 

// These are our enumerated constants.
enum 
{
    ARGS1 = 1,
    ARGS2 = 2,
    NO_ZERO = 98,
    ALLOW_ZERO = 99
};

// Prototypes for helper functions
int DataCheck(int, int, ...); // Elipses indicate a variable amount of variables
int Help(void);
int Menu(void);

// Non-recursive function prototypes
int Sum(int);
int SquareSum(int);
int Fib(int);
int Gcd(int, int);
int Pow(int, int);
int Prnt(int);
int Tri1(int);
int Tri2(int);

// Recursive prototypes
int RecFib(int);
int RecSum(int);
int RecSquareSum(int);
int RecGcd(int, int);
int RecPow(int, int);
int RecPrnt(int);
int RecTri1(int);
int RecTri2(int);

/* The DataCheck function takes a number a flag saying if this instance
 * allows for zero as an input, and then a flag indicating the number
 * of variables after it. (1 or 2).
 *
 * An example of DataCheck: DataCheck(ALLOW_ZERO, ARGS2, num1, num2);
 * This tells us that for this instance of the function zero is allowed,
 * there are two arguments, and they are num1 and num2.
 */

int DataCheck(int zero_allowed, int i, ...)
{
    int num1 = 0, num2; 
    if(zero_allowed == 99)
        num2 = 0;
    else
        num2 = 1;
    
    // These two functions are defined in stdarg.h
    va_list nums;
    va_start(nums, i);

    // If we pass in more than 2 arguments set the second one, otherwise it's
    // 0 or 1 depending on the earlier if statement.
    num1 = va_arg(nums, int);
    if(i > 1)
        num2 = va_arg(nums, int);
    
    if(num1 > 10000 || num2 > 10000)
    {
        printf("Your input was too large! Since this program uses recursion please\nKeep input under 10000. Thank you!\n");
        va_end(nums);
        fflush(stdin);
        return 0;
    }
    
    // Two different cases if zero is allowed or not.
    switch(zero_allowed)
    {
        case 98:
            if(num1 < 1 || num2 < 1)
            {
                printf("This function does not allow zero or negative numbers. Please try a number larger than zero!\n");
                va_end(nums);
                return 0;
            }
            else
                break;
        case 99:
            if(num1 < 0 || num2 < 0)
            {
                printf("This function allows zero, but not negative numbers. Try a zero or larger!\n");
                va_end(nums);
                return 0;
            }     
            else
                break;
    }

    va_end(nums);
    return 1;
}

/* What the user sees if they type 12 at the lab01 prompt. This function
 * exists incase the user forgets what the different codes are.
 */

int Menu(void)
{
    printf("Enter a number (1 - 8) to select which function to preform, enter 9 to exit.\n");
    printf("To see a description of this program enter 10. Enter 11 to clear the screen.\n");
    printf("To see this message again, enter 12 at the Main Prompt 'lab01>'\n");

    return 1;
}

/* Our help function, what the user sees if they type 10 at the
 * lab01 prompt. It's just a printf, no explanation needed.
 */

int Help(void)
{
    printf("\n*********************************************\n"
           "* This program, written by Zach Easterbrook *\n"
           "* preforms 8 basic functions in 2 different *\n"
           "* ways. It handles bad user input and it is *\n"
           "* presented in a organized way so it's easy *\n"
           "* to read. The source code is clean as well *\n"
           "*********************************************\n\n"
           "To read about individual functions please consult\n"
           "the source code.\n\n");
    
    return 1;
}

/* Start main */

int main(void)
{
	char choice[BUFSIZ];    // Hold any garbage input from the main input screen
    int choice2;
	int sum, sqsum, fibnum; // Variables for non-recursive functions. 1 - 3
	int gcd1, gcd2, pow1, pow2, pnum; // Variables for non-recursive functions 4 - 6
	int triup, tridown; // Variables for non-recursive functions 7-8

    /* We use a do-while loop to control our decision menu
     * inside this loop we preform a switch-case structure
     * since the choice is an int variable, and switch-cases
     * can only be preformed on ints
     */
    system("clear");
    Menu();
    do
	{
        printf("lab01> ");
        scanf("%s", choice);
        if(!sscanf(choice, "%d", &choice2)) // Using this, we force an integer input
            continue;
        if(DataCheck(NO_ZERO, ARGS1, choice2))
        {
            /* ALL of the switch cases work in this manner:
             * Get the input, it must be an integer. Unfortunately a char will
             * crash the program.
             * See if the integer passes our checks using the DataCheck
             * function defined earlier.
             * Execute the function, as well as the recursive function.
             * Exit the case and present the menu.
             *
             * Failure to input correct numbers will return to the main
             * menu with an error message.
             */

            switch(choice2)
            {
                case 1:
                    printf("Enter a positive integer for function 1.\n");
                    scanf("%d", &sum);
                    if(DataCheck(NO_ZERO, ARGS1, sum))
                    {
                        Sum(sum);
                        printf("Recursive: %d\n", RecSum(sum));
                        break;
                    }
                    else
                        break;
                case 2:
                    printf("Enter a positive integer for function 2.\n");
                    scanf("%d", &sqsum);
                    if(DataCheck(NO_ZERO, ARGS1, sqsum))
                    {
                        SquareSum(sqsum);
                        printf("Recursive: %d\n", RecSquareSum(sqsum));
                        break;
                    }
                    else
                        break;
                case 3:
                    printf("Enter the nth Fibonacci number to find.\n");
                    scanf("%d", &fibnum);
                    if(DataCheck(NO_ZERO, ARGS1, fibnum))
                    {
                        Fib(fibnum);
                        printf("Recursive: %d\n", RecFib(fibnum));
                        break;
                    }
                    else
                        break;
                case 4:
                    printf("Enter two numbers to computer the gcd of\n");
                    scanf("%d %d", &gcd1, &gcd2);
                    if(DataCheck(ALLOW_ZERO, ARGS2, gcd1, gcd2))
                    {
                        Gcd(gcd1, gcd2);
                        printf("Recursive: %d\n", RecGcd(gcd1, gcd2));
                        break;
                    }
                    else
                        break;
                case 5:
                    printf("Enter two numbers, the second will be the power applied to the first.\n");
                    scanf("%d %d", &pow1, &pow2);
                    if(DataCheck(ALLOW_ZERO, ARGS2, pow1, pow2))
                    {
                        Pow(pow1, pow2);
                        printf("Recursive: %d\n", RecPow(pow1, pow2));
                        break;
                    }
                    else
                        break;
                case 6:
                    printf("Enter a number so we can print n .. 1.\n");
                    scanf("%d", &pnum);
                    if(DataCheck(NO_ZERO, ARGS1, pnum))
                    {
                        Prnt(pnum);
                        printf("Recursive: ");
                        RecPrnt(pnum);
                        printf("\n");
                        break;
                    }
                    else
                        break;
                case 7:
                    printf("Enter the size of triangle to draw.\n");
                    scanf("%d", &tridown);
                    if(DataCheck(NO_ZERO, ARGS1, tridown))
                    {
                        Tri1(tridown);
                        printf("Recursive:\n");
                        RecTri1(tridown);
                        break;
                    }
                    else
                        break;
                case 8:
                    printf("Enter the size of the triangle to draw.\n");
                    scanf("%d", &triup);
                    if(DataCheck(NO_ZERO, ARGS1, triup))
                    {
                        Tri2(triup);
                        printf("Recursive:\n");
                        RecTri2(triup);
                        break;
                    }
                    else
                        break;
                case 9:
                    printf("Exiting.\n");
                    break;
                case 10:
                    Help();
                    break;
                case 11:
                    system("clear");
                    break;
                case 12:
                    Menu();
                    break;
                default:
                    printf("Unrecognized function reference. Try typing 12.\n");
                break;
            }        
		}
	}
	while(choice2 != 9);

    return 0;
}
 
/* This function takes a number n, and returns the sum of the digits up to n
 * The input parameters are one number, num- it must be positive, or zero.
 * Once it has this number, it will computer the digit sum and print that number.
 */

int Sum(int num)
{
	int x, res = 0;
	for(x = 0; x <= num; ++x)
		res += x;
	printf("Non-recursive: %d\n", res);
	
	return 1;
}

/* This function takes a number and computes the sum of (i + 1)^2 + .. + (n + 1) ^2
 * where i starts at 1 and n is the number we input.
 * It takes one number, n, as input this must be a positive integer.
 * It will print the result of the previously mentioned formula.
 */

int SquareSum(int num)
{
	int x, res = 0;
	for(x = 1; x <= num; ++x)
		res += ((x + 1) * (x + 1));
	printf("Non-recursive: %d\n", res);

    return 1;
}

/* Takes a number as input and outputs the nth digit in the fibonacci sequence
 * which is, 1 + 1 + 2 + 3 + 5 + 8 + 13 + 21, etc., so this function receiving
 * 8 as input will return 21.
 */

int Fib(int num)
{
	int x1 = 0, x2 = 1, x3, fib;
	if(num >= 1)
	{
		for(x3 = 2; x3 <= num; x3++)
		{
			fib = x1 + x2;
			x1 = x2;
			x2 = fib;
		}
	}
	printf("Non-recursive: %d\n", fib);

    return 1;
}	

/* Returns the gcd of a number, the gcd can be defined with the formula
 * gcd(x,y) = gcd(y, x mod y)
 */

int Gcd(int num1, int num2)
{
    int rem, quo, div;
    while(num2 != 0)
    {
        rem = num1 % num2;
        quo = num1 / num2;
        rem = num1 - (num2 * quo);
        num1 = num2;
        num2 = rem;
    }

    div = num1;
    printf("Non-recursive: %d\n", div);

    return 1;
}

/* This takes two numbers, a and b, and applies b to a in the form of an
 * exponent
 */

int Pow(int num1, int num2)
{
    int res = 0, x, num3 = num1;
    if(num2 == 0)
    {    
        printf("Non-recursive: 1\n");
        return 1;
    }
    else
    {
        for(x = 1; x < num2; ++x)
        {
            res = num1 * num3;
            num1 = res;
        }
    }
    printf("Non-recursive: %d\n", res);

    return 1;
}

/* This takes a number n and prints n .. 1 in descending
 * order.
 * Example: n = 5. prints: 5 4 3 2 1
 */

int Prnt(int num)
{
    printf("Non-recursive: ");
    for(; num > 0; num--)
        printf("%d ", num);
    printf("\n");

    return 1;
}

/* Take a number n and prints n stars then n - 1 stars on the next line
 * until n = 1, where it prints 1 star and then exits. This forms an
 * upside down triangle.
 */

int Tri1(int num)
{
    int x = num;
    printf("Non-recursive:\n");
    for(; num > 0; num--)
    {    
        for(; x > 0; x--)
            printf("*");
        printf("\n");
        x = num - 1;
    }

    return 1;
}

/* Take a number n and prints 1 star, prints 2 stars on the next line,
 * etc., till we have printed n stars. This forms a right-side up
 * triangle.
 */

int Tri2(int num)
{
    int x, y, z = 1;
    printf("Non-recursive:\n");
    for(x = 0; x < num; ++x)
    {
        for(y = 0; y < z; ++y)
            printf("*");
        printf("\n");
        ++z;
    }

    return 1;
}

/* From this point on all functions are recursive, a decision was made to use
 * Cs ternary operater ?: (Deitel Chapter 3, page 60)
 * The operator is the same thing as saying:
 * if(condition)
 *      expression(); // Upon returning true
 * else
 *      expression(); // Upon returning false
 *
 * Once this is known, these functions are quite easy to read and very
 * intuitive since they only take up one line of code.      
 */

// ======================RECURSIVE FUNCTIONS START=============================

/* This function takes a number n, and returns the sum of the digits up to n
 * The input parameters are one number, num- it must be positive, or zero.
 * Once it has this number, it will computer the digit sum and print that number.
 */

int RecSum(int num)
{
	return num <= 1 ? num : num + RecSum(num - 1);
}

/* This function takes a number and computes the sum of (i + 1)^2 + .. + (n + 1) ^2
 * where i starts at 1 and n is the number we input.
 * It takes one number, n, as input this must be a positive integer.
 * It will print the result of the previously mentioned formula.
 */

int RecSquareSum(int num)
{
    return num <= 0 ? num : ((num + 1) * (num + 1)) + RecSquareSum(num - 1);
}

/* Takes a number as input and outputs the nth digit in the fibonacci sequence
 * which is, 1 + 1 + 2 + 3 + 5 + 8 + 13 + 21, etc., so this function receiving
 * 8 as input will return 21.
 */

int RecFib(int num)
{ 
	return num < 2 ? num : RecFib(num - 1) + RecFib(num - 2);
}

/* Returns the gcd of a number, the gcd can be defined with the formula
 * gcd(x,y) = gcd(y, x mod y)
 */

int RecGcd(int num1, int num2)
{
    return num2 == 0 ? num1 : RecGcd(num2, num1 % num2);
}

/* This takes two numbers, a and b, and applies b to a in the form of an
 * exponent
 */

int RecPow(int num1, int num2)
{
    return num2 == 0 ? 1 : num1 * RecPow(num1, num2 - 1);
}

// Unfortunately the last three functions are impossible to write using the
// ternary operator.

/* This takes a number n and prints n .. 1 in descending
 * order.
 * Example: n = 5. prints: 5 4 3 2 1
 */

int RecPrnt(int num)
{
    if(num == 1)
        printf("%d ", num);
    else
    {    
        printf("%d ", num);
        RecPrnt(num - 1);
    }

    return 1;
}

/* Take a number n and prints n stars then n - 1 stars on the next line
 * until n = 1, where it prints 1 star and then exits. This forms an
 * upside down triangle.
 */

int RecTri1(int num)
{
    int x;

    if(num == 0)
        return 1;
    else
    {
        for(x = 0; x < num; ++x)
            printf("*");
        printf("\n");
        RecTri1(num - 1);
    }

    return 1;
}

/* Take a number n and prints 1 star, prints 2 stars on the next line,
 * etc., till we have printed n stars. This forms a right-side up
 * triangle.
 */

int RecTri2(int num)
{
    int x;

    if(num == 1)
        printf("*\n");
    else
    {
            RecTri2(num - 1);
            for(x = 0; x < num; ++x)
                printf("*");
            printf("\n");
    }

    return 1;
}

/* Written by: Zachary Easterbrook
 * Student ID: 103163420 
 * Written on: September 12th, 2011
 * Email: easterbz@uwindsor.ca
 * 
 * This code has been tested on:
 * -SunOS sol 5.10 Generic_137111-08 sun4u sparc SUNW,Sun-Fire-880
 * -SunOS luna 5.10 Generic_144500-19 sun4u sparc SUNW,Sun-Fire-880
 * -Linux ltsp-bravo 2.6.32-4-pve #1 i686 i686 i386 GNU/Linux
 * -Linux 2.6.39-ARCH #1 i686 Intel(R) Core(TM)2 Duo CPU T6400 @ 2.00GHz GenuineIntel GNU/Linux
 *
 * It has been successfully compiled with:
 * -gcc version 4.6.1 (GCC) 
 * -gcc version 4.3.3 (GCC)
 */

#include <stdio.h>

/* Function Prototypes begin */

/*
 * Returns the length of str. The length of a C string is determined by the
 * terminating null-character.
 * A C string is as long as the amount of characters between the beginning
 * of the string and the terminating null character
 */
int strlen(const char *str);

/*
 *  Copies the C string pointed by src into the array pointed by dest,
 *  including the terminating null character.
 */
char *strcpy(char *dest, const char *src);

/*
 * Appends a copy of the src string to the dest string. The terminating null
 * character in dest 
 * is overwritten by the first character of src, and a new null-character is
 * appended at the end of the new 
 * string formed by the concatenation of both in dest.
 * dest is returned by the function.
 */
char *strcat(char *dest, const char *src);

/*
 * Compares the C string str1 to the C string str2.
 * This function starts comparing the first character of each string. If
 * they are equal to each other, it continues 
 * with the following pairs until the characters differ or until
 * a terminanting null-character is reached.
 * Returns an integral value indicating the relationship between the
 * strings:
 * A zero value indicates that both strings are equal.
 * A value greater than zero indicates that the first character that
 * does not match has a greater value in str1 than in str2; 
 * And a value less than zero indicates the opposite.
 */
int strcmp(const char * str1, const char * str2);

/* Function Prototypes ends */

// Begin the main function
int main(int argc, char *argv[])
{
  // This program takes two command line arguments.
  // We check if our length is 3 because argv[0] holds
  // the program name.
  if (argc != 3)
  {
    printf("Wrong number of arguments passed.\n");
    return -1;
  }

  // Declare two pointers to strings that point two our two arguments passed.
  // We also declare a third string with a modest size so we can copy things
  // to it and show off our functions.
  char *string1 = argv[1];
  char *string2 = argv[2];
  char string3[255];

  // Get the length of our strings
  int strlen1 = strlen(string1);
  int strlen2 = strlen(string2);



  // Output the length
  printf("strlen(%s) = %d\n", string1, strlen1);
  printf("strlen(%s) = %d\n", string2, strlen2);

  // Get the difference. The meaning of the value returned by strcmp is 
  // documented in the function prototype.
  int difference = strcmp(string1, string2);
  if (difference == 0)
    printf("%s == %s\n", string1, string2);
  else if (difference < 0)
    printf("%s < %s\n", string1, string2);
  else
    printf("%s > %s\n", string1, string2);

  // We copy string 1 to string 3 so we leave string 1 intact
  strcpy(string3, string1);
  // Then we concat string2 onto string 3.
  // It is important to understand why we did not concat string2
  // onto string1, string1 points to argv[1] which has a set size.
  // Since string2 is pointing to argv[2], and it is contiguous in memory with
  // regards to argv[1], we risk overwriting pieces of argv[2] if we concat
  // string 2 onto string 1.
  printf("strcat(%s, %s) = %s\n", string1, string2, strcat(string3, string2));
  
  return 0;
}

// See function prototype for full documentation
int strlen(const char *str)
{
  int i = 0;
  // While the string is not equal to the null character we increment the
  // pointer and our counter respectively.
  while (*str != '\0', *str++) 
    ++i;
 
  return i;
}

// See function prototype for full documentation
char *strcpy(char *dest, const char *src)
{
  char *save = dest;
  /* while the src pointer is not null, we increment
   * the destination pointer and source pointer, after 
   * we have copied the information at these locations 
   * (from src -> dest)
   */
  do
    *dest = *src;
  while (*src, *dest++, *src++);

  return save;
}

// See function prototype for full documentation
char *strcat(char *dest, const char *src)
{
  char *save = dest;
  // While dest is not null increment this pointer. This puts us at the end of
  // the string.
  while (*dest) ++dest;
  // This means "copy the stuff at src to dest then increment both addresses,
  // keep doing this until we can not make the contents of the address at dest
  // equal to the contents of the address at src" 
  while (*dest++ = *src++);

  return save;
}

// See function prototype for full documentation
int strcmp(const char *str1, const char* str2)
{
  // if the character at str1 and str2 are the same, we enter the for loop and
  // increment both these addresses. If str1 is 0 (the null terminator), we're
  // done checking and we know they've been equal otherwise we would not have
  // gotten this far, so we return true.
  for (; *str1 == *str2; ++str1, ++str2)
    if (*str1 == 0)
      return 0;

  // We cast str1 and str2 to pointers to const unsigned chars, then dereference those
  // to access the elements. We subtract them, and it'll either come back
  // positive or negative.
  return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

/* Written by: Zachary Easterbrook
 * Student ID: 103163420
 *
 * This program takes an integer argument and then attempts to
 * read that position from a file (nums.bin). 
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  // Buffer for the item
  int item[1];

  // If argc isn't two we print an error and exit
  if (argc != 2)
  {
    fprintf(stderr, "You must enter exactly 1 argument\n");
    exit(1);
  }

  // atoi is the function "Ascii to integer", it will converted the string
  // argument in argv[1] to an integer argument.
  int pos = atoi(argv[1]);

  FILE *fp;
  
  // Open the file for reading and make sure it opened correctly
  fp = fopen("nums.bin", "r");
  if (fp == NULL)
  {
    perror("Error");
    exit(1);
  }

  // We want to seek to pos - 1 * sizeof(int), because we're reading integers
  // and the file will start at 0 so we need to do the -1. I.e, if we passed
  // position 1 to this program that is position 0 in the file.
  fseek(fp, (pos - 1) * sizeof(int), SEEK_SET);
  // Read the item as an integer
  fread(item, sizeof(int), 1, fp);

  printf("%d\n", *item);
  fclose(fp);
  return EXIT_SUCCESS;
}

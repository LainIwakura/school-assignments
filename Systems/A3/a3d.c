/* Written by: Zachary Easterbrook
 * Student ID: 103163420
 * 
 * This program sorts numbers in nums.bin and then rewrites 
 * them to the file in sorted order.
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// We pass this as a function pointer to the qsort function
// provided by stdlib.h
int compare(const void * a, const void * b)
{
  return (*(int*)a - *(int*)b);
}

int main(int argc, char *argv[])
{
  int item[1];
  int items[BUFSIZ];
  int j, i = 0;

  FILE *fp;
  
  fp = fopen("nums.bin", "r");
  if (fp == NULL)
  {
    perror("Error");
    exit(1);
  }

  // While we're not at the end of the file we keep building the array
  while (!feof(fp))
  {
    fread(item, sizeof(int), 1, fp);
    items[i++] = *item;
  }
  // Sort the items and then close the file
  qsort(items, i, sizeof(int), compare);
  fclose(fp);
  
  // Open the file again, but in writing mode
  fp = fopen("nums.bin", "w");
  if (fp == NULL)
  {
    perror("Error");
    exit(1);
  }

  j = i;
  i = 0;
  // Write the numbers into the file.
  for (; i < j; ++i)
  {
    fwrite(items + i, sizeof(int), 1, fp); 
    // Uncomment next line to see numbers being printed
    //printf("%d\n", items[i]); 
  }

  fclose(fp);

  return EXIT_SUCCESS;
}

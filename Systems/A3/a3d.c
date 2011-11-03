#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

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

  while (!feof(fp))
  {
    fread(item, sizeof(int), 1, fp);
    items[i++] = *item;
  }
  qsort(items, i, sizeof(int), compare);
  fclose(fp);
  
  fp = fopen("nums.bin", "w");
  if (fp == NULL)
  {
    perror("Error");
    exit(1);
  }

  j = i;
  i = 0;
  for (; i < j; ++i)
    fwrite(items + i, sizeof(int), 1, fp); 

  fclose(fp);

  return EXIT_SUCCESS;
}

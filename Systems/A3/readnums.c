#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  int item[1];

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
    printf("%d\n", *item);
  }
  fclose(fp);
  return EXIT_SUCCESS;
}

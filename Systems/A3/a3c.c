#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  int item[1];

  if (argc != 2)
  {
    fprintf(stderr, "You must enter exactly 1 argument\n");
    exit(1);
  }

  int pos = atoi(argv[1]);

  FILE *fp;
  
  fp = fopen("nums.bin", "r");
  if (fp == NULL)
  {
    perror("Error");
    exit(1);
  }

  fseek(fp, (pos - 1) * sizeof(int), SEEK_SET);
  fread(item, sizeof(int), 1, fp);

  printf("%d\n", *item);
  fclose(fp);
  return EXIT_SUCCESS;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
  char fileName[9] = "nums.bin";
  srand(time(NULL));
  int count = 1 + rand() % 50;
  int *nums = malloc(count*sizeof(int));
  int i = 0;
  FILE *fp = fopen(fileName, "w");
  if (fp == NULL)
  {
    fprintf(stderr, "File %s can not be openned\n", fileName);
    return 1;
  }
  for (i = 0; i < count; i++)
    nums[i] = rand() % 1000;

  fwrite(nums, sizeof(int), count, fp);
  fclose(fp);

  return 0;
}

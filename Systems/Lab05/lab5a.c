/* Lab5a
 * Written by: Zachary Easterbrook
 * Written on: Oct 31st 2011
 * Student ID: 103163420
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Return if a number is even or odd
 * return 0 means even
 * return 1 means odd
 */
int evenOdd(int n)
{
  return ((n % 2 == 0) ? 0 : 1);
}

void setHalves(int par, int *i, int *j, int fSize)
{
  if (par == 0)
  {
    *j = fSize / 2;
    *i = fSize / 2;
  }
  else
  {
    *j = (fSize / 2) + 1;
    *i = fSize / 2;
  }
}

// Print reverse string
void prstr(char * str, int len)
{
  while (len > 0, len--)
    printf("%c", str[len]);
  printf("\n");
}

// Print a reverse string to a file
void prstrf(char * str, int len, FILE *f)
{
  while (len > 0, len--)
    fprintf(f, "%c", str[len]);
}

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    fprintf(stderr, "Please provide the input file's name\n");
    exit(1);
  }

  FILE *file1, *file2;
  long fSize;
  int parity, firstHalf = 0, secondHalf = 0;
  char *buff, *outfile;
  int length = 0;

  if (argc == 3)
  {
    outfile = argv[2];
    file2 = fopen(argv[2], "wb");
    if (file2 == NULL)
    {
      fputs("File error\n", stderr);
      exit(1);
    }
  }

  file1 = fopen(argv[1], "rb");
  if (file1 == NULL)
  {
    fputs("File error\n", stderr);
    exit(1);
  }

  fseek(file1, 0, SEEK_END);
  fSize = ftell(file1);
  fSize -= 1;
  rewind(file1);

  parity = evenOdd(fSize);
  setHalves(parity, &firstHalf, &secondHalf, fSize);

  buff = (char *)malloc(sizeof(char) * secondHalf);
  fseek(file1, firstHalf, SEEK_SET);
  fread(buff, 1, secondHalf, file1);
  if (argc == 3)
  {
    fwrite(buff, 1, secondHalf, file2);
  }
  else
    printf("%s", buff);
  rewind(file1);
  
  buff = (char *)malloc(sizeof(char) * firstHalf);
  fread(buff, 1, firstHalf, file1);
  if (argc == 3)
  {
    prstrf(buff, strlen(buff), file2);
  }
  else
    prstr(buff, strlen(buff));

  return 0;
}

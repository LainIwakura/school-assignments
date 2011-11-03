#include <fcntl.h>
//#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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

char * rmemstr(char * str)
{
  int i = 0;
  int j = strlen(str) - 1;
  while (i < j)
  {
    str[i] ^= str[j];
    str[j] ^= str[i];
    str[i] ^= str[j];
    ++i;
    --j;
  }
  return str;
}

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    //fprintf(stderr, "Please provide the input file's name\n");
    exit(1);
  }

  int file1, file2;
  long fSize;
  int parity, firstHalf = 0, secondHalf = 0;
  char buff[1024], *outfile;
  char *buff2, *buff3;
  int length = 0;

  if (argc == 3)
  {
    outfile = argv[2];
    file2 = open(argv[2], O_WRONLY);
    if (file2 == -1)
    {
      //fputs("File error\n", stderr);
      exit(1);
    }
  }

  file1 = open(argv[1], O_RDONLY);
  if (file1 == -1)
  {
    //fputs("File error\n", stderr);
    exit(1);
  }

  fSize = read(file1, buff, 1024);
  fSize -= 1;

  parity = evenOdd(fSize);
  setHalves(parity, &firstHalf, &secondHalf, fSize);
  buff2 = (char *)malloc(sizeof(char) * secondHalf);
  lseek(file1, firstHalf, SEEK_SET);
  read(file1, buff2, secondHalf);
  if (argc == 3)
  {
    write(file2, buff2, secondHalf);
  }
  else
    write(STDOUT_FILENO, buff2, secondHalf);

  lseek(file1, 0, SEEK_SET);
  buff3 = (char *)malloc(sizeof(char) * firstHalf);
  read(file1, buff3, firstHalf);
  rmemstr(buff3);
  if (argc == 3)
  {
    write(file2, buff3, firstHalf);
  }
  else
    write(STDOUT_FILENO, buff3, firstHalf);
  
  return 0;
}

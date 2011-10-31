#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  if (argc == 1)
    fprintf(stderr, "Please provide the input file's name");

  return 0;
}

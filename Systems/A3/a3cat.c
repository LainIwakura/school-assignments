/* a3cat.c - A simple implementation of the UNIX cat utility
 * Written by - Zachary Easterbrook
 * Written on - Oct 24th / 2011
 * Student ID: 103163420
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void cat_std();
void cat_file(int, char **, int);

int main(int argc, char *argv[])
{
  char opt;

  opt = getopt(argc, argv, "n");

  switch (argc)
  {
    case 1:
      cat_std();
      break;
    case 2:
      if (opt != 'n')
        cat_file(argc, argv, 0);
      else if (opt == 'n')
        fprintf(stderr, "Error: -n option must have at least 1 argument\n");
      break;
    default:
      if (opt != 'n')
        cat_file(argc, argv, 0);
      else if (opt == 'n')
        cat_file(argc, argv, 1);
      break;
  }
  
  return EXIT_SUCCESS;
}

void cat_std()
{
  char line[BUFSIZ];
  while (fgets(line, BUFSIZ, stdin) != NULL)
    printf("%s", line);
}

void cat_file(int numFiles, char *files[], int linesOn)
{
  int i = 0;
  int j = 1;
  FILE *fp;
  char line[BUFSIZ];

  if (linesOn == 1)
    i += 1;

  for (i += 1; i < numFiles; i++)
  {
    if ((fp = fopen(files[i], "r")) != NULL)
    {
      while (fgets(line, BUFSIZ, fp))
      {
        if (linesOn == 1)
          printf("     %d  %s", j++, line);
        else
          printf("%s", line);
      }
      fclose(fp);
    }
    else
      fprintf(stderr, "%s: %s: No such file or directory\n", files[0], files[i]);
  }
}

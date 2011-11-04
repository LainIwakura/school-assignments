/* a3cat.c - A simple implementation of the UNIX cat utility
 * Written by - Zachary Easterbrook
 * Written on - Oct 24th / 2011
 * Student ID: 103163420
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Two prototypes. The first function will read from STDIN,
 * whereas the second function will read from files given in
 * the char ** array. Alternatively, in this function the stream could
 * be switched to STDIN using -.
 */
void cat_std(int, int *);
void cat_file(int, char **, int);

int main(int argc, char *argv[])
{
  // Our option
  char opt;

  // Get an option matching n
  opt = getopt(argc, argv, "n");

  // Switch based on our number of arguments
  switch (argc)
  {
    // One argument, meaning only the file was executed. We read from STDIN
    case 1:
      cat_std(0, 0);
      break;
    // Two arguments, we check if there is a -n, if there is then we print an
    // error because -n needs at least one argument passed to it.
    // If there is no -n we just print the contents of the file
    case 2:
      if (opt != 'n')
        cat_file(argc, argv, 0);
      else if (opt == 'n')
        fprintf(stderr, "Error: -n option must have at least 1 argument\n");
      break;
    default:
      // If there are more than 2 args we just print all of the files with lines
      // on or with lines off. It depends on if the -n is specified or not.
      if (opt != 'n')
        cat_file(argc, argv, 0);
      else if (opt == 'n')
        cat_file(argc, argv, 1);
      break;
  }
  
  return EXIT_SUCCESS;
}

// Function to take input from STDIN and print it to STDOUT. Lines are optional.
// Note: If lines are on and STDIN is not the last argument line numbers stay
// updated after control is passed back to our cat_file function.
void cat_std(int linesOn, int *curLine)
{
  char line[BUFSIZ];
  while (fgets(line, BUFSIZ, stdin) != NULL)
  {
    // If the lines are on print the line number then increment it.
    if (linesOn == 1)
      printf("     %d  %s", (*curLine)++, line);
    else
      printf("%s", line);
  }
}

// Function to read a file given in our *files array.
void cat_file(int numFiles, char *files[], int linesOn)
{
  int i = 0;
  // Sort of hackish here but whatever it works..
  int j = 1;
  int *jPtr = &j;
  FILE *fp;
  char line[BUFSIZ];

  // If lines are on this means the -n option was passed
  // and we need to start at an index 1 higher than usual in
  // the files array.
  if (linesOn == 1)
    i += 1;

  // We will always at the least start at 1, sometimes however
  // we start at 2.
  for (i += 1; i < numFiles; i++)
  {
    // If the file is simply a dash, we switch control over to the cat_std
    // function
    if (*(files[i]) == '-')
    {
      cat_std(1, jPtr);
    }
    // Otherwise we simply open the file and read through it.
    else if ((fp = fopen(files[i], "r")) != NULL)
    {
      while (fgets(line, BUFSIZ, fp))
      {
        if (linesOn == 1)
          printf("     %d  %s", (*jPtr)++, line);
        else
          printf("%s", line);
      }
      fclose(fp);
    }
    else
    {
      fprintf(stderr, "%s: %s: No such file or directory\n", files[0], files[i]);
    }
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function builds up an array of strings based on our tokens
// This makes swapping incredibly easy since we just have to change
// The array indexes.
void build_token_arr(char *t[], char *s)
{
  int i = 0;
  char *token;
  token = strtok(s, " ");
  while (token != NULL)
  {
    t[i] = token;
    ++i;
    token = strtok(NULL, " ");
  }
}

int main(int argv, char *argc[])
{
  if (argv != 3)
  {
    fprintf(stderr, "Error: The program needs exactly 2 arguments.\n");
    exit(1);
  }

  FILE *file1;                  // Old file we read from
  FILE *file2;                  // New file we write to
  char *old_filename = argc[1]; // Old filename
  char *new_filename = argc[2]; // New filename
  char *tok_arr[4];             // A 2D array for our tokens
  char line[BUFSIZ];            // To go through the file line by line 
  float new_num;                // Need this to store a float value from the string..thing..yeah...

  // We just get file 2 prepared here so it's not buried far in the other
  // if / while / switch statements...
  file2 = fopen(new_filename, "w");
  if (file2 == NULL)
  {
    perror("Error");
    exit(1);
  }

  if ((file1 = fopen(old_filename, "r")) != NULL)
  {
    while (fgets(line, BUFSIZ, file1)) 
    {
      // Without this function, we'd have much more than 3 lines in our while
      // loop! Note that we are actually passing a reference here..the actual
      // memory will be modified so the values don't fall out of scope when
      // the function call is done.
      build_token_arr(tok_arr, line);
      sscanf(tok_arr[3], "%f", &new_num);
      fprintf(file2, "%s %s %s %.2f\n", tok_arr[0], tok_arr[2], tok_arr[1], new_num);
    }
    fclose(file1);
  }
  else
    perror("Error");

  fclose(file2);

  return EXIT_SUCCESS;
}

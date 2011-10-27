#include <stdio.h>
#include <stdlib.h>

int main()
{
  char line[BUFSIZ];
  char *c;

  fgets(line, BUFSIZ, stdin);
  for (c = line; *c != '\0'; *c++)
    if (*c != ' ')
      printf("%c", *c);

  return EXIT_SUCCESS;
}

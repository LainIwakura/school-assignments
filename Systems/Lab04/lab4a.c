#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  char line[BUFSIZ];
  char *c;
  
  fgets(line, BUFSIZ, stdin);
  c = line;

  while(*c != '\n') {
    switch (*c) {
      // I hope you remember ASCII...
      case 'a': *c = (*c - 48); break; // ASCII 'a' = 97, ASCII '1' = 49. 97 - 49 = 48. Ergo, 97 - 48 = 49 (ASCII '1')
      case 'e': *c = (*c - 51); break; // Repeat for the appropriate values..
      case 'i': *c = (*c - 54); break;
      case 'o': *c = (*c - 59); break;
      case 'u': *c = (*c - 64); break;
    }
    printf("%c", *c++);
  }
  printf("\n");

  return EXIT_SUCCESS;
}

/* a3_fgets() - A simple fgets implementation
 * Written by: Zachary Easterbrook
 * Written on: Oct 24th 2011
 * Student ID: 103163420
 */

// For system calls...
#include <unistd.h>
#include <fcntl.h>
//#include <stdio.h>

char * a3_fgets(char * str, int num, int stream)
{
  read(stream, str, num);
  str[num] = '\0';

  return str;
}

int main()
{
  char line[1024];
  a3_fgets(line, 1024, STDIN_FILENO);
  //printf("%s", line);
  return 0;
}

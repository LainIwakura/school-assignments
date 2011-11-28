/* Written by: Zachary Easterbrook
 * Student ID: 103163420
 *
 * This program will mimic some basic IPC using files..not a good
 * way to do it but hey assignment is assignment.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define DEBUG(msg) fprintf(stderr, "%s:%s:%d: %s\n", __FILE__, __FUNCTION__, __LINE__, msg)

int factorial(int);
void child(int [2]);
void parent(int [2]);

int main(int argc, char *argv[])
{
  pid_t pid;
  int fd[2];

  if (pipe(fd) < 0)
  {
    write(1, "Pipe Failed\n", 12);
    return 1;
  }
  else if ((pid = fork()) == 0)
  {
    child(fd);
  }
  else
  {
    parent(fd);
  }
}

int factorial(int x)
{
  return (x == 0 ? 1 : factorial(x - 1) * x);
}

void child(int f[2])
{
  char input[2];
  int count = 0;
  close(f[0]);
  printf("Enter a number less than 12: ");
  while (1)
  {
    fflush(stdout);
    count = read(STDIN_FILENO, input, sizeof(char) * 2);
    write(f[1], input, count);
    //sleep(1);
  }
  close(f[1]);
}

void parent(int f[2])
{
  int num;
  char cnum[2];
  close(f[1]);
  while (1)
  {
    read(f[0], cnum, sizeof(char) * 2);
    sscanf(cnum, "%d", &num);
    printf("Factorial of %d is %d\n", num, factorial(num));
    printf("Enter a number less than 12: ");
    fflush(stdout);
  }
  close(f[0]);
}

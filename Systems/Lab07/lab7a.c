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

unsigned long long factorial(unsigned long long x)
{
  return (x == 0 ? 1 : factorial(x - 1) * x);
}

int main(int argc, char *argv[])
{
  pid_t pid;

  unsigned long long input_num = 0;
  int c_pid, p_pid; // Child pid, Parent pid
  FILE *file1, *file2;


  if ((pid = fork()) == 0)
  {
#ifdef MY_DEBUG
    DEBUG("STEP 2");
#endif
    while (1)
    {
      printf("Enter a number, preferably less than 12: ");
      scanf("%llu", &input_num);
      printf("%llu\n", factorial(input_num));
    }
  }
  else
  {
    while (1)
    {
    }
#ifdef MY_DEBUG
    DEBUG("STEP 6");
#endif
  }
}

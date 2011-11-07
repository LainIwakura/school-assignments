#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    fprintf(stderr, "This program must take 2 arguments\n");
    exit(1);
  }

  int check;
  int fp;

  // Directory name
  char *dirn = argv[1];
  // File name
  char *file = argv[2];
  pid_t pid;
  int ppid;
  char filename[1024] = "";
  char ppid_string[6];

#ifdef DEBUG
    printf("Executing: %s at %d: ", __FILE__, __LINE__);
    printf("Current PID: %d ", getpid());
    printf("Current PPID: %d\n", getppid());
#endif

  if ((pid = fork()) == 0)
  {
    ppid = getppid();
    sprintf(ppid_string, "%d", ppid);

    ppid_string[5] = '\0';

    strcat(filename, "result_");
    strcat(filename, ppid_string);

    if ((fp = open(filename, O_RDWR | O_CREAT)) == -1)
    {
      perror("open");
      return 1;
    }

    dup2(fp, STDOUT_FILENO);
    dup2(fp, STDERR_FILENO);
    close(fp);

    check = execlp("find", "find", dirn, "-name", file, (char *)0);  
    if (check < 0)
    {
      write(2, "exec failed\n", 12);
      exit(1);
    }
  }
  else
    wait(&check);

  return 0;
}

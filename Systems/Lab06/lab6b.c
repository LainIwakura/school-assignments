#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int child_jobs(const char *);

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    fprintf(stderr, "This program must take 2 arguments\n");
    exit(1);
  }

  char *file1 = argv[1];
  char *file2 = argv[2];

  pid_t pid1;
  pid_t pid2;
  pid_t pid3;

  int check1;
  int check2;
  int check3;

  if ((pid1 = fork()) == 0)
  {
    check1 = child_jobs(file1);
    if (check1 < 0)
    {
      write(2, "process failed\n", 15);
      exit(1);
    }
    exit(0); // Exit first process
  }
  else
    wait(&check1);
  
  if ((pid2 = fork()) == 0)
  {
    check2 = child_jobs(file2);
    if (check2 < 0)
    {
      write(2, "process failed\n", 15);
      exit(1);
    }
    exit(0);  // Exit second process
  }
  else
    wait(&check2);

  if ((pid3 = fork()) == 0)
  {
    check3 = execl("addnum", "addnum", file1, file2);
    if (check3 < 0)
    {
      write(2, "process failed\n", 15);
      exit(1);
    }
    exit(0); // Exit third process
  }
  else
    wait(&check3);

  return 0;
}

int child_jobs(const char *fname)
{
  FILE *fp;
  char buff[1024];
  char *tok;
  int sum = 0;
  int temp;

  if ((fp = fopen(fname, "r")) != NULL)
  {
    if (fgets(buff, 1024, fp) != NULL)
    {
      tok = strtok(buff, " ");
      while (tok != NULL)
      {
        temp = atoi(tok);
        sum += temp;
        tok = strtok(NULL, " ");
      }
    }
  }
  
  fclose(fp);

  if ((fp = fopen(fname, "w")) != NULL)
  {
    fprintf(fp, "%d", sum);
  }

  fclose(fp);

  return 0;
}

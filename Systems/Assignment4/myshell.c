/* A program meant to simulate a basic shell
 *
 *
 * Written by: Zachary Easterbrook
 * Student ID: 103163420
 * Written on: Nov 9th, 2011
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>

#define DEBUG(msg) fprintf(stderr, "%s:%s:%d: %s\n", __FILE__, __FUNCTION__, __LINE__, msg)

pid_t my_fork();
int process_args(char *, char **);

int main(int argc, char *argv[])
{
  pid_t pid;
  char *line, *arg_list[255], name[BUFSIZ];
  char *tok;
  int status, i;

  line = malloc(sizeof(char) * 255);
    
  printf("\n\n\t***************************\n");
  printf("\t*  Welcome to our Shell!  *\n");
  printf("\t*  'exit' or 'quit' to    *\n");
  printf("\t*      exit! Enjoy!       *\n");
  printf("\t***************************\n\n");

  while (1)
  {
    printf("LainShell: ");
    fgets(line, 255, stdin);
    if (line[strlen(line) - 1] == '\n')
      line[strlen(line) - 1] = '\0';

    if (strlen(line) == 0)
      continue;

    tok = strtok(line, ";");
    while (tok != NULL)
    {
      line += strlen(tok) + 1;
      process_args(tok, arg_list);
      tok = strtok(line, ";");
      if (strcmp(arg_list[0], "exit") == 0 || strcmp(arg_list[0], "quit") == 0)
        exit(0);
      
      pid = my_fork();
      
      if (pid == -1)
      {
        perror("Fork failed!\n");
        exit(1);
      }
      else if (pid > 0)
      {
        wait(&status);
      }
      else
      {
        if (execvp(arg_list[0], arg_list) == -1)
        {
#ifdef MY_DEBUG
        DEBUG(arg_list[0]);
#endif
          int i = 0;
          while (arg_list[i] != NULL)
            printf("%d:\t%s\n", i, arg_list[i++]);
          perror("Child process could not exec");
          exit(22);
        }
      }
    }
  }
  
  return 0;
}

int process_args(char *line, char **arg_list)
{
  int i = 0;
  char *token;
  token = strtok(line, " ");
  while (token != NULL)
  {
    arg_list[i] = (char *)malloc(255);
    strcpy(arg_list[i], token);
#ifdef MY_DEBUG
    DEBUG(arg_list[i]);
#endif
    token = strtok(NULL, " ");
    ++i;
  }
  arg_list[i] = NULL;
  return 0;
}

pid_t my_fork()
{
  static int count = 0;
  return (++count <= 20) ? fork() : -1;
}

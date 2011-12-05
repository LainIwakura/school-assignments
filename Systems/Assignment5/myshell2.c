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

// Just for debugging. Compile with gcc -DMY_DEBUG to see debugging messages.
#define DEBUG(msg) fprintf(stderr, "%s:%s:%d: %s\n", __FILE__, __FUNCTION__, __LINE__, msg)

pid_t my_fork();
int process_args(char *, char **,  int *);
int exec_pipe(char *);
int count_pipes(char *);

int main(int argc, char *argv[])
{
  pid_t pid;
  char *line, *arg_list[255], name[BUFSIZ];
  char *tok;
  int status, i;
  int bgfg;

  line = malloc(sizeof(char) * 255);
    
  printf("\n\n\t***************************\n");
  printf("\t*  Welcome to our Shell!  *\n");
  printf("\t*  'exit' or 'quit' to    *\n");
  printf("\t*      exit! Enjoy!       *\n");
  printf("\t***************************\n\n");

  while (1)
  {
    printf("LainShell: ");
    fflush(stdout);
    fgets(line, 255, stdin);
    // If the last character is a newline we set it to a null-terminator
    if (line[strlen(line) - 1] == '\n')
      line[strlen(line) - 1] = '\0';

    if (strlen(line) == 0)
      continue;

    // Check for a pipe, if there is we'll go straight into the exec_pipe
    // function. For consistency we can't really reuse the below parent / child
    // code but we can reuse the process_args function.
    if (strstr(line, "|"))
    {
      exec_pipe(line);
      // Execute the pipe'd command and go to the next iteration of the while
      // loop. 
      continue;
    }

    // Tokenize based on ;
    tok = strtok(line, ";");
    while (tok != NULL)
    {
      // Save our position in the line so when we retokenize we're at the next
      // token. We can't use NULL because strtok in process_args overwrites it.
      line += strlen(tok) + 1;
      process_args(tok, arg_list, &bgfg);
      tok = strtok(line, ";");
      // If they typed exit or quit..we exit 
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
        // If this flag was set by process args we run in the background
        if (bgfg == 1)
        {
          waitpid(pid, &status, WNOHANG);  
        }
        else
        {
          // Otherwise the foreground
          wait(&status);
        }
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

int process_args(char *line, char **arg_list, int *bgfg)
{
  char *pos;
  // Checking if it's a background process and setting a flag if it is.
  if ((pos = strstr(line, "&")) != NULL)
  {
    *pos = '\0';
    *bgfg = 1;
  }
  else
  {
    *bgfg = 0;
  }

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

int exec_pipe(char *cmd)
{
  int num_pipes = 0;
  int fd[2];
  int bgfg = 0; // Never run background commands with pipes.
  char original_cmd[255];
  char *tok, prog1[256], prog2[256], *arg_list1[255], *arg_list2[255];

  strcpy(original_cmd, cmd);
  num_pipes = count_pipes(cmd);

  // Only support for singly piped commands.
  if (num_pipes > 1)
  {
    printf("The shell currently doesn't support multiple pipes! Sorry!\n");
    return 0;
  }
  else
  {
    // Get our two programs
    // They have arguments.
    tok = strtok(original_cmd, "|");
    strcpy(prog1, tok);
    tok = strtok(NULL, " |");
    strcpy(prog2, tok);

    // Process our arguments
    process_args(prog1, arg_list1, &bgfg);
    process_args(prog2, arg_list2, &bgfg);

    pipe(fd);
    // Execute prog1
    if (fork() > 0)
    {
      close(fd[0]);
      dup2(fd[1], 1);
      execvp(arg_list1[0], arg_list1);
      exit(22);
    }
    else
    {
      close(fd[1]);
      dup2(fd[0], 0);
      execvp(arg_list2[0], arg_list2);
      exit(22);
    }
  }

  return 1;
}

int count_pipes(char *cmd)
{
  char *tok;
  int num = 0;
  tok = strtok(cmd, "|");
  while (tok != NULL)
  {
    tok = strtok(NULL, "|");
    ++num;
  }

  return num - 1;
}

pid_t my_fork()
{
  static int count = 0;
  return (++count <= 20) ? fork() : -1;
}

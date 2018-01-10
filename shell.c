#include "header.h"

/*
  char ** parse_args(char * line, char delimiter)
  Description:
    Parses the given string using the given delimiter
  Arguments:
    char * line -> A pointer to the original string
    char delimiter -> The character that is going to be used to parse the string
  Return Value:
    A char ** which consists of the parsed strings
*/
char ** parse_args(char * line, char delimiter) {
  int size = 6;
  char ** s1 = (char **)malloc(size * sizeof(char *));

  int i = 0;
  char * pos;
  // Parse the string using the given delimiter
  while(line){
    s1[i] = strsep(&line, &delimiter);
    // If there is newline, make it null
    if ((pos=strchr(s1[i], '\n')) != NULL) {
      *pos = '\0';
    }
    i++;
  }
  // Put a terminating null pointer at the end
  s1[i] = 0;
  return s1;
}

/*
  void redir_in(char ** args)
  Description:
    Implements redirecting in by writing to a file
  Arguments:
    char ** args -> A pointer to the original string
  Return Value:
    N/A
*/
void redir_in(char ** args){
    //printf("this happened!\n");
    int cmd, file, i;
    i = 0;
    //printf("%s\n",args[3]);
    while (args[i]) {
      if (strcmp(args[i],">") == 0){
        break;
      }
      i++;
    }
    //printf("this is i: %d\n", i);
    file = i + 1;
    int fd, b, c;
    fd = open(args[file], O_CREAT | O_WRONLY | O_TRUNC | O_RDONLY, 0644);
    b = dup(STDOUT_FILENO);
    c = dup2(fd, STDOUT_FILENO);
    args[i]=0;
    exec_one(args);
    dup2(b,c);
    exit(0);
}

/*
  void exec_one(char ** args)
  Description:
    Forks off a child process and the child process calls execvp to execute the given command
  Arguments:
    char ** args -> Command line arguments that should be executed
  Return Value:
    N/A
*/
void exec_one(char ** args) {
  // Fork off a child process
  int f = fork();
  if (f == 0) {
    // Child process

    // Exit if the command is exit or cd
    if(!strcmp(args[0], "exit") || !strcmp(args[0], "cd")) {
      exit(0);
    }
    if (args[1]){
      int i = 0;
      while (args[i]) {
        if (strchr(args[i], '>') != NULL) {
          //printf("IT WAS FOUND!! \n");
          redir_in(args);
          break;
        }
        i++;
      }
    }
    int i = 0;
    i = execvp(args[0], args);

    // If there was something went wrong, print out the error

    if (i < 0) {
      printf("-bash: %s: %s \n", args[0], strerror(errno));
    }
    exit(0);
  }
}

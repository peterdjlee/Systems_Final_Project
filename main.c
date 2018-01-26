#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
void exec_one(char ** args);

//PARSE ARGS METHOD
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
    printf("this happened!\n");
    int cmd, file, i;
    i = 0;
    //printf("%s\n",args[3]);
    while (args[i]) {
      if (strcmp(args[i],">") == 0){
        break;
      }
      i++;
    }
    printf("this is i: %d\n", i);
    printf("this is the thing at i: %s\n", args[i]);
    file = i + 1;
    int fd, b, c;
    fd = open(args[file], O_CREAT | O_WRONLY | O_TRUNC | O_RDONLY, 0644);
    b = dup(STDOUT_FILENO);
    c = dup2(fd, STDOUT_FILENO);
    args[i]=0;
    execvp(args[0], args);
    dup2(b,c);
    exit(0);
}

int main(int argc, char *argv[]){
  printf("\nCOMPILING AND RUNNING YOUR CODE...\n");

  //getting the name of the file from the command line
  char line[100];
  strcpy(line, argv[1]);

  //creating: "gcc -o code filename.c"
  char cmdline1[100];
  strcpy(cmdline1, "gcc -o code ");
  strcat(cmdline1, line);

  //creating: "./a.out > filename"
  char cmdline2[100];
  strcpy(cmdline2, "./code > ");
    //remove .c from the string
  int length = strlen(line);
  int i;
  char filename[100];
  for (i = 0; i < length - 2; i++){
    filename[i] = line[i];
  }
  strcat(cmdline2, filename);
  //printf("%s\n",cmdline1);
  //printf("%s\n",cmdline2);

  int status = 0;

  //forks of a process that compiles the code file
  int f = fork();
  if (f == 0) { // child process
    char ** cmd = parse_args(cmdline1, ' ');
    int i;
    //printf("arg 0: %s\narg 1: %s\narg 2: %s\narg 3: %s\narg 4: %s\n", cmd[0], cmd[1], cmd[2], cmd[3], cmd[4]);
    i = execvp(cmd[0], cmd);
  }
  else if (f < 0) { //fork failed
    printf("fork failed :(\n");
  }
  else { //
    int returnStatus;
    waitpid(f, &returnStatus, 0);  // Parent process waits here for child to terminate.

  }

  //forks off a process to redirect the ./code to a new file
  f = fork();
  if (f == 0) { // child process
    char ** cmd2 = parse_args(cmdline2, ' ');
    //printf("arg 0: %s\narg 1: %s\narg 2: %s\n", cmd2[0], cmd2[1], cmd2[2]);
    redir_in(cmd2);
    printf("this finished\n");
    exit(0);
  }
  else if (f < 0) { //fork failed
    printf("fork failed :(\n");
  }
  else { //
    int returnStatus;
    waitpid(f, &returnStatus, 0);  // Parent process waits here for child to terminate.

  }
  printf("THEN this finished\n");

  return 0;
}

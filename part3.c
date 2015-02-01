#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>


// Main function to fork the processes
int main()
{
  pid_t pid1, pid2, childpid;

  // Parameterss for execv calls
  //char *const emptyparams[] = {NULL};
  char *const params1[] = {"/usr/bin/time","-f","\%e time elapsed, with \%P CPU. \%c involuntary context-switches, \%w voluntary context switches (I/O)","./bin/syscall_writer", NULL};
  char *const params2[] = {"/usr/bin/time","-f","\%e time elapsed, with \%P CPU. \%c involuntary context-switches, \%w voluntary context switches (I/O)","./bin/stdlibrary_writer", NULL};
  //char *const params2[] = {"--verbose", "./bin/stdlibrary_writer", NULL};

  // Create the child processes for syscall_writer
  printf("Creating children processes...\n");
  pid1 = fork();
  if (pid1 == 0) {
    execv("/usr/bin/time",params1);
  }
  else if(pid1 < 0) {
    fprintf(stderr,"Error making child for syscall_writer\n");
    exit(1);
  }

  // Second child - for stdlib_writer
  pid2 = fork();
  if(pid2 == 0) {
    execv("/usr/bin/time",params2);
  }
  else if(pid2 < 0) {
    fprintf(stderr,"Error making child for stdlib_writer\n");
    exit(1);
  }

  // Wait for the processes to finish 
  printf("Waiting for the children to finish...\n");
  childpid = wait(NULL);
  if(childpid == pid1) {
    printf("The syscall_writer process finished first\n");
  }
  else if(childpid == pid2) {
    printf("The stdlib_writer process finished first\n");
  }
  else {
    fprintf(stderr,"Error occured waiting for the child\n");
  }
  // Wait for the other child
  childpid = wait(NULL);
  if(childpid == pid1) {
    printf("The syscall_writer process finished last\n");
  }
  else if(childpid == pid2) {
    printf("The stdlib_writer process finished last\n");
  }
  else {
    fprintf(stderr,"Error occured waiting for the child\n");
  }

  return 0;
}





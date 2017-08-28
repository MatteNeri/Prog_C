/* simple_pipe.c

   Simple demonstration of the use of a pipe to communicate
   between a parent and a child process.

   Usage: simple_pipe "string"

   The program creates a pipe, and then calls fork() to create a child process.
   After the fork(), the parent writes the string given on the command line
   to the pipe, and the child uses a loop to read data from the pipe and
   print it on standard output.
*/
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
 
#define BUF_SIZE 10

void errExit(char *str)
{
  fprintf(stderr, "%s", str);
  perror("");
  exit(1);
}

int
main(int argc, char *argv[])
{
  int pfd[2];                             /* Pipe file descriptors */
  char buf[BUF_SIZE];
  ssize_t numRead;
 
  if (argc != 2 || strcmp(argv[1], "--help") == 0)
    fprintf(stderr, "%s string\n", argv[0]);
 
  if (pipe(pfd) == -1)                    /* Create the pipe */
    errExit("pipe");
 
  switch (fork()) {
  case -1:
    errExit("fork");
 
  case 0:             /* Child  - reads from pipe */
    if (close(pfd[1]) == -1)            /* Write end is unused */
      errExit("close - child");
 
    for (;;) {              /* Read data from pipe, echo on stdout */
      numRead = read(pfd[0], buf, BUF_SIZE);
      if (numRead == -1)
	errExit("read");
      if (numRead == 0)
	break;                      /* End-of-file */
      if (write(STDOUT_FILENO, buf, numRead) != numRead)
	errExit("child - partial/failed write");
    }
 
    write(STDOUT_FILENO, "\n", 1);
    if (close(pfd[0]) == -1)
      errExit("close");
    _exit(EXIT_SUCCESS);
 
  default:            /* Parent - writes to pipe */
    if (close(pfd[0]) == -1)            /* Read end is unused */
      errExit("close - parent");
 
    if (write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
      errExit("parent - partial/failed write");
 
    if (close(pfd[1]) == -1)            /* Child will see EOF */
      errExit("close");
    wait(NULL);                         /* Wait for child to finish */
    exit(EXIT_SUCCESS);
  }
}

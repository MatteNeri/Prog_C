#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* ESERCIZIO: bloccare questo programma subito prima della return, e verificare che PID e PPID
   siano quelli stampati. */

int main( void )
  {
    printf( "My parent is %d, I am %d\n", getppid(), getpid() );
    return EXIT_SUCCESS;
  }

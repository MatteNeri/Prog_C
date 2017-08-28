#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* vedere anche sigsuspend */

/* ESERCIZIO: verificare le differenze tra pause e sigsuspend */

int main( void )
  {

    /* set an alarm to go off in 5 seconds */
    alarm( 5 );

    /*
     * Wait until we receive a SIGALRM signal. However,
     * since we don't have a signal handler, any signal
     * will kill us.
     */
    printf( "Hang around, "
        " waiting to die in 5 seconds\n" );
    pause();
    return EXIT_SUCCESS;
  }

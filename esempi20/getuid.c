#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/* ESERCIZIO: fare in modo che venga stampato anche il nome dell'utente */

int main( void )
  {
    printf( "My userid is %d\n", getuid() );
    return EXIT_SUCCESS;
  }

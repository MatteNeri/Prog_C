#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main( void )
  {
    gid_t ogid;

    ogid = getgid();
    if( setgid( 2 ) == -1 ) {
       perror( "setgid" );
       return EXIT_FAILURE;
    }
    printf( "group id is now 2, was %d\n", ogid );
    return EXIT_SUCCESS;
  }

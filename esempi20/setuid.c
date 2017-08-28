/*
 * This process sets its userid to 0 (root)
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

/*

  eseguire setuid.script (da utente superuser)
  
*/

int main( void )
{
    uid_t ouid;

    ouid = getuid();
    if( setuid( 0 ) == -1 ) {
        perror( "setuid" );
        /* return EXIT_FAILURE; */
    }
    else

      printf( "userid %d switched to 0\n", ouid );
    if (chmod("setuid", 04777)) {
        perror( "chmod" );
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/* ESERCIZIO: fare in modo che venga stampato anche il nome del gruppo */

int main( void )
{
    printf( "I belong to group ID %d\n", getgid() );
    return EXIT_SUCCESS;
}


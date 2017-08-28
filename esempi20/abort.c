#include <stdlib.h>

/* ESERCIZIO: verificare che effettivamente questo processo riceva un segnale SIGABRT */

/* ESERCIZIO: verificare che effettivamente questo processo non abbia EXIT_SUCCESS come
   exit status */

int main( void )
{
    int major_error = 1;

    if( major_error )
        abort();

    /* You'll never get here. */
    return EXIT_SUCCESS;
}

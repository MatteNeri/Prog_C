#include <stdio.h>
#include <stdlib.h>

/* ESERCIZIO: capire dal man la differenza tra exit ed _exit, e dare un esempio in cui si
   comportano diversamente */

int main( int argc, char *argv[] )
{
    FILE *fp;

    if( argc <= 1 ) {
        fprintf( stderr, "Missing argument\n" );
        exit( EXIT_FAILURE );
    }

    fp = fopen( argv[1], "r" );
    if( fp == NULL ) {
        fprintf( stderr, "Unable to open '%s'\n", argv[1] );
        exit( EXIT_FAILURE );
    }
    fclose( fp );
    exit( EXIT_SUCCESS );
    
    /*
     You'll never get here; this prevents compiler
     warnings about "function has no return value".
    */
    return EXIT_SUCCESS;
}

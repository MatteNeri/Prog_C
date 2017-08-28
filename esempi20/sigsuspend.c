/*
 * This program pauses until a signal other than
 * a SIGINT occurs. In this case a SIGALRM.
 */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

sigset_t    set;

/* ESERCIZIO: verificare il corretto funzionamento di questo programma */

int main( void )
{
  sigemptyset( &set );
  sigaddset( &set, SIGINT );

  printf( "Program suspended and immune to breaks.\n" );
  printf( "A SIGALRM will terminate the program"
	  " in 10 seconds.\n" );
  alarm( 10 );
  sigsuspend( &set ); /* essenzialmente, prima fa sigprocmask(&set) e poi si sospende (va in
			 stato di blocked). Dallo stato di blocked, questo processo puo'
			 essere rivitalizzato solo da un segnale (che pero' non deve essere
			 in set...); a quel punto si procede con la normale esecuzione
			 (a meno che il segnale sia privo di handler e abbia come azione di
			 default la terminazione) */
  /* piu' completa di pause, che non puo' bloccare nessun segnale  */
  return( EXIT_SUCCESS );
}

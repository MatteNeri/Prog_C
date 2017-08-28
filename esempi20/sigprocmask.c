#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* ESERCIZIO: aggiungere tutti i controlli mancanti sui possibili errori delle syscall */

/* ESERCIZIO: scrivere una funzione print_set che prenda un sigset_t e stampi i segnali in esso
   contenuti (usare sigpending e sigismember dentro un for) */

/* ESERCIZIO: modificare questo programma in modo tale che, ogni 5 secondi, controlli se
   l'utente ha premuto CTRL+C o CTRL+Z o abbia inviato un SIGUSR1, e in tal caso si limiti
   a scrivere sullo stdout tale evento */

int main( void )
{
  sigset_t set, oset, pset;

  sigemptyset( &set ); /* il contrario e' sigfillset, che mette tutti i segnali nel set */
  sigaddset( &set, SIGINT ); /* il contrario e' sigdelset, che toglie un segnale dal set */
  sigaddset( &set, SIGUSR1 ); 
  sigprocmask( SIG_BLOCK, &set, &oset );
  /* inizio sezione critica */

  sigpending( &pset );
  /* chiamare print_set(&pset) */
  printf("dentro\n");

  kill( getpid(), SIGINT );
  kill( getpid(), SIGUSR1 );

  printf("ancora dentro\n");
  sigpending( &pset );
  /* chiamare print_set(&pset) */

  /* fine sezione critica */
  sigprocmask( SIG_UNBLOCK, &set, &oset );
  printf("fuori\n");

  /* The program terminates with a SIGINT */
  return( EXIT_SUCCESS );
}

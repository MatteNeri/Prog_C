#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/* ESERCIZIO: catturare anche SIGUSR2, limitandosi a cambiare la frase di default che scrive */

/* ESERCIZIO: fare in modo, nell'esercizio precedente, che l'handler di SIGUSR1 blocchi SIGUSR2 e viceversa */

/* ESERCIZIO: aggiungere tutti i controlli mancanti sui possibili errori delle syscall */

int main( void )
  {
    void handler();
    struct sigaction act;
    sigset_t set; /* insieme di segnali (simile all'insieme di fd della select...) */

    sigemptyset( &set ); /* set = {} */
    sigaddset( &set, SIGUSR1 ); /* set = {SIGUSR1} */
    sigaddset( &set, SIGUSR2 ); /* set = {SIGUSR1, SIGUSR2} */

    act.sa_flags = 0; /* questo campo serve principalmente per chiarire alcuni usi di SIGCHLD,
			 ma c'e' anche SA_NODEFER, vedere il man  */
    act.sa_mask = set; /* i segnali in set sono "masked": se arriveranno mentre l'handler e'
			  in esecuzione, verranno messi in attesa (nel qual caso, si sta gia'
			  gestendo un SIGUSR1...) */
    act.sa_handler = &handler; /* puntatore alla funzione (di cui e' stato dato il prototipo
				  come prima istruzione del main) */
    sigaction( SIGUSR1, &act, NULL );

    printf("send %d\n", SIGUSR1);
    kill( getpid(), SIGUSR1 ); /* si manda da solo un SIGUSR1 */

    /* Program will terminate with a SIGUSR2 */
    return EXIT_SUCCESS;
  }

void handler( int signo )
  {
    static int first = 1; /* static: la variabile e' locale alla funzione (non puo' essere
			     acceduta al di fuori di questa funzione), ma il suo valore viene
			     mantenuto da chiamata a chiamata */

    printf("start %d\n", signo);
    
    if( first ) {
      first = 0;
      printf("send %d\n", SIGUSR1);
      kill( getpid(), SIGUSR1 );  /* non viene invocato di nuovo, ma una volta finito
				     l'handler arriva comunque al processo che invoca
				     nuovamente l'handler, ma first sara' 0... */
      printf("send %d\n", SIGUSR2);
      kill( getpid(), SIGUSR2 );  /* non viene invocato di nuovo, ma una volta finito
				     l'handler arriva comunque al processo che scrive
				     "User defined signal 2" e viene
				     terminato (e' l'azione standard di SIGUSR2) */
    }
    /* ESERCIZIO: verificare che i due segnali mandati sopra sono pendenti, e non cancellati */
    printf("end %d\n", signo);
  }


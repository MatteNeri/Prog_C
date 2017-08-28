#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

/* VECCHIO (deprecated) modo di gestire i segnali: syscall signal */

/* ESERCIZIO: rifare questo programma usando sigaction (vedere l'esempio sigaction.c) */

sig_atomic_t signal_count = 0; /* quando si accede ad un sig_atomic_t (che e' un intero),
				  il processo non puo' essere interrotto (almeno, non da
				  un signal handler) */

void MyHandler( int sig_number )
  {
    /* la dichiarazione di signal_count poteva essere spostata qui dentro? */
     ++signal_count;
  }

int main( void )
  {
    int dummy;
    /* ESERCIZIO: aggiungere gli opportuni controlli sul valore di ritorno delle syscall  */
    signal( SIGUSR1, MyHandler );   /* se arriva SIGUSR1, allora anziche' effettuare l'azione
				       standard (vedere qual e' da man 7 signal) chiama
				       myHandler(SIGUSR1) */
    signal( SIGABRT, SIG_DFL );    /* se arriva SIGABRT, fai l'azione di default (man 7 signal);
				      sembrerebbe inutile, ed in questo esempio semplice lo e';
				      ma in generale prevedere SIG_DFL serve per annullare un
				      precedente handler (cosicche', un segnale che arrivi
				      in un certo momento puo' essere gestito in un modo, se
				      arriva in un altro momento viene gestito con l'azione
				      standard*/
    signal( SIGFPE, SIG_IGN );     /* terza possibilita': SIG_IGN; il segnale viene ignorato */
    printf("%d\n", getpid());
    scanf("%d", &dummy);
    printf("%d\n", signal_count);
    return (EXIT_SUCCESS);
  }

/* ESERCIZIO: verificare il corretto funzionamento del programma */

/* ESERCIZIO: cosa succede se si prova a fare qualcosa di diverso da SIG_DFL con SIG_KILL, SIG_CONT, SIG_STOP, SIG_TSTP? */

/* ESERCIZIO: normalmente, se si avvia un programma in foreground e poi si preme Ctrl+C, il programma termina. Scrivere un programma che non termina se si preme Ctrl+C */


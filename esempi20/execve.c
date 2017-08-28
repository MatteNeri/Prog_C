#include <unistd.h>
#include <stdio.h>

/* ESERCIZIO: realizzare lo stesso comportamento con setenv e/o putenv (vedere setenv.c) */

int main() {
  char *argv[2], *envp[3];
  argv[0] = "print_env"; /* assegnamento anomalo, andrebbe fatto a tempo di dichiarazione: e' ok solo perche' non si ha intenzione di modificare la stringa "print_env" */
  argv[1] = (char *)0;
  envp[0] = "key1=val1";
  envp[1] = "key2=val2";
  envp[2] = (char *)0;
  execve("./print_env", argv, envp);
  /* se la exec ha successo, la parte di programma che esegue la exec stessa non esiste piu':
     l'effetto della exec e' proprio quello di sostituire in toto l'attuale processo, codice
     compreso. */
  perror("execve fallita"); /* se si e' arrivati qui, puo' essere solo per il fallimento dell'
			       execve */
}

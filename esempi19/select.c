#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#define BUFF_SIZE 10

/* ESERCIZIO: modificare questo programma in modo tale che copi man mano quanto viene
   scritto su stdin su un file dato come primo argomento. Ogni riga immessa da stdin
   (anche a distanza di secondi) deve essere messa nel file il piu' presto possibile.
   Usare fflush o fsync per essere sicuri che le scritture su file avvengano subito
   dopo la scrittura, oppure O_SYNC al momento dell'apertura del file */

int
main(void)
{
  fd_set rfds;
  struct timeval tv;
  int retval;
  char buffer[BUFF_SIZE];

  /* Watch stdin (fd 0) to see when it has input. */
  FD_ZERO(&rfds); /* l'insieme di file descriptor rdfs e' adesso vuoto */
  FD_SET(0, &rfds); /* l'insieme di file descriptor rdfs contiene adesso il solo 0
		       (file descriptor dello stdin) */

  /* Wait up to five seconds. */
  tv.tv_sec = 5;
  tv.tv_usec = 0;

  /* monitora lo stdin per 5 secondi; passando NULL come ultimo argomento, la select
     sarebbe bloccante; mettendo tutti e 2 i campi di tv a 0, la select fa un solo
     controllo ed esce */
  retval = select(1, &rfds, NULL, NULL, &tv);
  /* Don't rely on the value of tv now! */

  if (retval == -1)
    perror("select()");
  else if (retval) { /* la select ritorna il numero di fd sbloccati; qui puo' essere solo 1 */
    printf("Data is available now.\n");
  /* FD_ISSET(0, &rfds) will be true. */
    retval = read(0, buffer, BUFF_SIZE);
    printf("Read %d bytes from stdin.\n", retval);
  }
  else /* retval vale 0, quindi ci sono 0 fd sbloccati... */
    printf("No data within five seconds.\n");


  exit(EXIT_SUCCESS);
}

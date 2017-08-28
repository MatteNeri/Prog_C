/*
  The simplest example of pipe I could think of
  Paul Krzyzanowski
*/
#include <stdlib.h>
#include <stdio.h> /* for printf */
#include <string.h> /* for strlen */

/* Questo programma comunica con se stesso con una pipe, prima scrivendoci e poi leggendo
   l'informazione scritta */

/* Wsempio in pratica abbastanza inutile (per comunicare con se' stesso, ad un processo
   basta usare le variabili...), ma serve a vedere il minimo sindacale sulle pipe */

/* ESERCIZIO: aggiungere i controlli mancanti sugli errori delle syscall */

/* ESERCIZIO: cosa succederebbe invertendo le operazioni, ovvero facendo prima la read e
   poi la write? Si puo' evitare che il processo si blocchi sulla read? */

/* ESERCIZIO: modificare questo programma in modo che legga un intero da riga di comando,
   lo scriva sulla pipe, e poi stampi su stdout quanto letto dalla pipe aumentato di 1 */

int main(int argc, char **argv) {
  int n;
  int fd[2]; /* verra' passato a pipe: sono 2 fd, uno per la scrittura (fd[1]) e uno per la
		lettura (fd[0]) */
  char buf[1025];
  char *data = "hello... this is sample data";
  pipe(fd); /* come aprire un file, ma:
	       1) non c'e' il nome del file, ne' le varie modalita' (si puo' solo decidere
	          tra O_NONBLOCK e O_CLOEXEC, ma allora serve usare pipe2);
	       2) ci sono due file descriptor anziche' uno */
  write(fd[1], data, strlen(data)); /* si scrive su fd[1]... */
  /* in pratica, la write di cui sopra ha l'effetto di rendere disponibili per una chiamata
     a read su fd[0] quei caratteri che sono stati scritti dalla write (ovvero, quelli in
     data) */
  if ((n = read(fd[0], buf, 1024)) >= 0) { /* ...e si legge da fd[0] */
    buf[n] = 0; /* terminate the string */
    printf("read %d bytes from the pipe: \"%s\"\n", n, buf);
  } else
    perror("read");
  exit(0);
}

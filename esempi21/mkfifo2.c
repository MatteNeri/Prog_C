#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

/* Simile pipebis.c, ma usando le fifo */

/* Le fifo sono un oggetto a meta' tra file e pipe: come i file e' possibile dar loro un nome
   (e infatti le fifo vengono anche chiamate "named pipes") e quindi far si' che le usino
   processi non imparentati (con le pipe, e' possibile solo la comunicazione tra un antenato
   e i suoi figli - nipoti); come le pipe, e' possibile sincronizzare letture e scritture
   (ovvero, una read su una fifo vuota si blocca finche' non avviene una write da parte di
   qualche altro processo). Notare tuttavia che esiste O_NONBLOCK... */

/* Conseguentemente, qui non c'e' alcuna fork; occorre lanciare 2 volte questo programma,
   la prima volta dicendogli di fare la parte sinistra della pipe (/bin/ls -al), la seconda
   dicendogli di eseguire la parte sinistra (/usr/bin/tr a-z A-Z). 
   A tal proposito, ogni invocazione richiede almeno un argomento (il nome della fifo);
   la parte sinistra non richiede altro che il nome della fifo, per la parte destra occorre
   un secondo argomento (qualsiasi). Riscontrare questo comportamento nel codice. Tra
   parentesi: e' possibile anche l'ordine di invocazione inverso?
   Infine: potrebbe sembrare che la prima invocazione si blocchi, ed
   in effetti e' cosi'. Per sbloccarla, e' sufficiente invocare
   anche la seconda parte (o in un'altra shell, o invocando la prima
   in background).
   Infine2: si puo' ottenere da shell lo stesso risultato con i seguenti comandi:
   mkfifo unnomedififo
   ls -al > unnomedififo &
   tr a-z A-Z < unnomedififo
*/

void runpipe();

int main(int argc, char **argv) {
  int status;
  int fd;
  struct stat res;
  /* se la fifo (il cui nome e' dato come argomento al programma) non esiste, crearla */
  /* notare che la fifo viene visualizzata come un file speciale (e' visibile con il
     comando ls) */
  if (stat(argv[1], &res)) {
    /* la syscall mkfifo assomiglia alla open con O_CREAT, solo che il file e' appunto
       non regolare ma speciale (di tipo fifo; vedere la prima lettera dell'output di ls -l);
       altra differenza: mkfifo si limita a creare la fifo ma non la apre (infatti c'e' la
       open poco piu' sotto) */
    /* il fatto di non essere un file regolare lo si vede dal fatto che la sua dimensione
       e' sempre 0 (non e' veramente su un disco, ma viene gestito direttmente dal kernel
       di Linux) */
    if (mkfifo(argv[1], S_IRUSR | S_IWUSR)) {
      perror("Unable to create named pipe");
      exit(6);
    }
  }
  else if (!S_ISFIFO(res.st_mode)) { /* macro che controlla il tipo di un file (funziona solo
					sul risultato si una stat) */
    fprintf(stderr, "File already exists and is not a named pipe\n");
    exit(5);
  }
  /* e' come un file: va aperto */
  fd = open(argv[1], argc == 3? O_RDONLY : O_WRONLY);
  if (fd == -1) {
    perror("Unable to open named pipe");
    exit(7);
  }
  runpipe(fd, argc == 3);
  if (close(fd)) {
    perror("Unable to close named pipe");
    exit(8);
  }
  return 0;
}

char *cmd1[] = { "/bin/ls", "-al", "/", 0 };
char *cmd2[] = { "/usr/bin/tr", "a-z", "A-Z", 0 };

void runpipe(int fd, int mode) {
  switch (mode) {
  case 1:
    dup2(fd, 0);
    execvp(cmd2[0], cmd2);
    perror(cmd2[0]);
  case 0:
    dup2(fd, 1);
    execvp(cmd1[0], cmd1);
    perror(cmd1[0]);
  default:
    fprintf(stderr, "Should never arrive here!\n");
  }
} 

/* ESERCIZI: gli stessi di pipebis.c */

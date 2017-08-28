/* pipe demo */ /* Paul Krzyzanowski */
#include <stdlib.h>
#include <stdio.h>

/* Esempio molto importante: e' cosi' che si realizzano le pipe tra processi.
   Essenzialmente, eseguire questo singolo programma e' equivalente a dare alla bash
   il seguente comando:
   /bin/ls -al / | /usr/bin/tr a-z A-Z
*/

void runpipe();

int main(int argc, char **argv) {
  int pid, status;
  int fd[2];
  pipe(fd);
  switch (pid = fork()) {
  case 0: /* child */
    runpipe(fd); /* fara' a sua volta un'altra fork */
    exit(0); /* finita la funzione runpipe, il figlio termina */
  case -1: /* error */
    perror("fork");
    exit(1);
  default: /* parent */
    /* abbastanza inutile, semplicemente aspetta di vedere se ci sono stati problemi
       nell'esecuzione del figlio, che si occupa di tutta la parte effettiva della
       computazione */
    while ((pid = wait(&status)) != -1) /* serve veramente fare un while qui?  */
      fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(status));
    break;
  }
  exit(0);
}

char *cmd1[] = { "/bin/ls", "-al", "/", 0 };
char *cmd2[] = { "/usr/bin/tr", "a-z", "A-Z", 0 };

void runpipe(int pfd[]) {
  int pid;
  switch (pid = fork()) {
  case 0: /* child */ /* quindi, e' il nipote del processo lanciato da riga di comando */
    /* questo e' il processo che eseguira' /usr/bin/tr; si tratta del processo che leggera'
       dalla pipe, quindi deve chiudere pfd[1] che e' la parte in scrittura */
    close(pfd[1]);
    /* per quanto riguarda l'altra parte della pipe, ovvero quella in lettura, si vuole
       far si' che coincida con (il fd del)lo stdin. Infatti, il comando "normale",
       ovvero /usr/bin/tr, legge da stdin, e qui NON lo vogliamo modificare. Infatti, ci sara'
       una exec del file "/usr/bin/tr" e quindi non e' possibile cambiare il codice sorgente
       di /usr/bin/tr (che potrebbe anche non essere disponibile). Tuttavia, sappiamo che
       /usr/bin/tr legge il suo input dal suo stdin: dicendo quindi che lo stdin deve
       diventare una copia di pfd[0] (questo e' l'effetto di dup2), si ha che tutto
       quello che /usr/bin/tr legge da stdin viene invece letto dalla parte in lettura della
       pipe. Questo e' esattamente quello che serve per far si' che l'input di
       /usr/bin/tr venga direttamente dalla pipe in lettura */
    dup2(pfd[0], 0);
    /* esecuzione di cmd2[0], ovvero di "/usr/bin/tr", con tutti i parametri dati nel
       vettore cmd2 (compreso cmd2[0] stesso, che quindi, in un certo senso, viene
       dato 2 volte) */
    execvp(cmd2[0], cmd2);
    /* questa parte di codice potra' essere eseguita solo se la execvp fallisce */
    perror(cmd2[0]);
  case -1:
    perror("fork");
    exit(1);
  default: /* parent */ /* questo rimane il figlio del processo lanciato da riga di comando */
    /* questo e' il processo che eseguira' /bin/ls; si tratta del processo che scrivera'
       il suo risultato sulla pipe, quindi deve chiudere pfd[0] che e' la parte in lettura */
    close(pfd[0]);
    /* per quanto riguarda l'altra parte della pipe, ovvero quella in scrittura, si vuole
       far si' che coincida con (il fd del)lo stdout. Infatti, il comando "normale",
       ovvero /bin/ls, scrive su stdout, e qui NON lo vogliamo modificare. Infatti, ci sara'
       una exec del file "/bin/ls" e quindi non e' possibile cambiare il codice sorgente
       di /bin/ls (che potrebbe anche non essere disponibile). Tuttavia, sappiamo che
       /bin/ls scrive il suo output sul suo stdout: dicendo quindi che lo stdout deve
       diventare una copia di pfd[1] (questo e' l'effetto di dup2), si ha che tutto
       quello che /bin/ls scrive su stdout finisce invece sulla parte in scrittura della
       pipe. Questo e' esattamente quello che serve per far si' che l'output di
       /bin/ls finisca sulla pipe in scrittura */
    dup2(pfd[1], 1);
    /* esecuzione di cmd1[0], ovvero di "/bin/ls", con tutti i parametri dati nel
       vettore cmd1 (compreso cmd1[0] stesso, che quindi, in un certo senso, viene
       dato 2 volte) */
    execvp(cmd1[0], cmd1);
    /* questa parte di codice potra' essere eseguita solo se la execvp fallisce */
    perror(cmd1[0]); 
  }
} 

/* ESERCIZIO: provare a scambiare padre con figlio nella runpipe: cosa succede? e' corretto?
   si puo' evitare? */

/* ESERCIZIO: rendere generico il programma, facendo in modo che i due comandi, con relativi
   argomenti, vengano presi da riga di comando. Per capire dove finisce il primo comando (e
   quindi dove inizia il secondo) fare si' che il primo argomento sia il numero di argomenti
   del primo comando */

/* ESERCIZIO: realizzare da codice una pipe tra 3 comandi  */

/* ESERCIZIO: generalizzare, facendo una pipe tra n comandi (quindi, il programma dapprima
   legge n, poi il numero di argomenti del primo comando, poi il primo comando con tutti gli
   argomenti, poi il numero di argomenti del secondo comando, poi il secondo comando con
   tutti gli argomenti, etc) */

/* Sono stati effettuati tutti i wait di tutti i figli? Se no, era possibile farlo? */

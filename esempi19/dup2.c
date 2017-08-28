#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
 
#include <stdlib.h>
#include <stdio.h>

/* versione piu' interessante di dup.c: qui viene realizzata, a tutti gli effetti, la redirezione dello stdout; ovvero, eseguire

   make dup2
   ./dup2
   
   e' equivalente a:

   cp dup2.c dup_mod.c
   #modifica dup_mod.c in modo che effettui solo la printf di MESSAGE
   make dup_mod.c
   ./dup.c > output

   ESERCIZIO: fare uno script che mostri quanto detto di sopra
*/

#define OUTPATH "output"
#define MESSAGE "Behold, Standard Out is now a file!"
 
int main() {
    /*First, we open a file for writing only"*/
    int outputfd = -1;
 
    outputfd = open(OUTPATH, O_WRONLY | O_CREAT | O_TRUNC,
		    S_IRWXU | S_IRGRP | S_IROTH); /* 3 argomenti, dato che c'e' anche O_CREAT
						     nel secondo argomento; il terzo argomento
						     a quali permessi ottali corrisponde? */
 
    /*If we have an error, we exit
    * N.B. file descriptors less than one are invalid*/
    if (outputfd < 0) {
        perror("open(2) file: " OUTPATH);
        exit(EXIT_FAILURE);
    }
 
    /*Next, we close Standard Out
    The lowest file descriptor will now
    be STDOUT_FILENO*/
    if (close(STDOUT_FILENO) < 0) {
        perror("close(2) file: STDOUT_FILENO");
        close(outputfd);
        exit(EXIT_FAILURE);
    }
    /* per essere precisi, la situazione ora e':
     stdin - aperto
     stdout - chiuso
     stderr - aperto */
 
    /*Afterwards, we duplicate outputfd onto STDOUT_FILENO,
    exiting if the descriptor isn't equal to STDOUT_FILENO*/
    /* la dup ritorna il piu' piccolo intero non usato come file descriptor; dato che 0 (ovvero stdin) e' aperto e 1 (stdout) no, ritornera' 1 == STDOUT_FILENO */
    if (dup(outputfd) != STDOUT_FILENO) {
        perror("dup(2)");
        close(outputfd); /*N.B. Remember to close your files!*/
        exit(EXIT_FAILURE);
    }
 
    close(outputfd); /* If everything succeeds, we may close the original file */
    printf("%s\n", MESSAGE); /* e' una printf normale, dovrebbe scrivere su stdout; ma per effetto di quanto fatto prima, scrive invece sul file di nome output */
 
    return EXIT_SUCCESS;
}

/* ESERCIZIO: fare lo stesso con lo stdin e lo stderr; fare anche in modo che il nome del file di output (ora fissato) sia un argomento di questo programma */

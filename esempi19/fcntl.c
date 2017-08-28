#include    <sys/types.h>
#include    <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* syscall estremamente flessibile: prende 2 o 3 argomenti, dei quali il primo
   e' un fd gia' aperto in qualche modo (non necessariamente con la open, ricordarsi
   di lezione 8), il secondo un comando da fare sull'fd (specificato tramite una qualche
   costante simbolica),  e il terzo e' un argomento opzionale per il comando dato come
   secondo argomento. Da notare che quest'ultimo argomento puo' essere un puntatore ad
   una struttura (per esempio, il comando F_SETLK prende un struct flock *), quindi i
   comandi possono in pratica prendere un qualsiasi numero di argomenti. */

/* ESERCIZIO: realizzare dup.c e dup2.c usando fcntl al posto di dup e dup2 */

int
main(int argc, char *argv[])
{

    int     accmode, val;

    if (argc != 2) {
      write(2, "usage: a.out <descriptor#>", strlen("usage: a.out <descriptor#>"));
      exit(2);
    }

    /* un modo per farsi dire com'e' stato aperto un fd. Se lo si e' fatto con un precedenza
       con la open, ovviamente lo si saprebbe; ma non e' sempre detto (vedere esempio di
       esecuzione del programma riportati alla fine) */
    if ( (val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0) {
      fprintf(stderr, "fcntl error for fd %d: ", atoi(argv[1]));
      perror("");
      exit(3);
    }

    /* val ha, al suo interno, sia le info di accesso che di file status; con O_ACCMODE
       si accede alle sole di accesso */
    accmode = val & O_ACCMODE;
    if      (accmode == O_RDONLY)   printf("read only");
    else if (accmode == O_WRONLY)   printf("write only");
    else if (accmode == O_RDWR)     printf("read write");
    else fprintf(stderr, "unknown access mode");

    /* in realta', si poteva fare cosi' (direttamente l'AND bit-a-bit) anche sopra */
    if (val & O_APPEND)         printf(", append");
    if (val & O_NONBLOCK)       printf(", nonblocking");
#if !defined(_POSIX_SOURCE) && defined(O_SYNC)
    if (val & O_SYNC)           printf(", synchronous writes");
#endif
    putchar('\n');
    exit(0);
}

/* $ ./fcntl 0 */
/* $ ./fcntl 1 */
/* $ ./fcntl 2 2>temp.foo */
/* $ ./fcntl 2 2>>temp.foo */
/* $ ./fcntl 5 */
/* $ ./fcntl 5 5<>temp.foo */
/* ESERCIZIO: fare in modo che
   ./fcntl 5
funzioni esattamente come
   ./fcntl 5 5<>temp.foo
*/

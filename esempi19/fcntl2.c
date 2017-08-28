#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* uso importante di fcntl: settare i lock sui file. */
/* eseguire questo programma su due console separatamente, e vedere come evolvono */
/* ESERCIZIO: creare un deadlock usando 2 file ed 1 programma (con 2 comportamenti
 distinti, da distinguere da riga di comando). */

int main (int argc, char* argv[])
{
 char* file = argv[1];
 int fd;
 struct flock lock;

 printf ("opening %s\n", file);
 /* Open a file descriptor to the file. */
 fd = open (file, O_WRONLY);
 /* qui manca il controllo dell'errore: aggiungerlo! */
 printf ("locking\n");
 /* Initialize the flock structure. */
 memset (&lock, 0, sizeof(lock));
 lock.l_type = F_WRLCK;
 /* Place a write (exclusive) lock on the file. */
 fcntl (fd, F_SETLKW, &lock);
 /* qui manca il controllo dell'errore: aggiungerlo! */
 /* attenzione: normalmente i lock sono "advisory", quindi cercare di scrivere un file
    sul quale un processo detiene un lock non ha l'effetto di bloccare la scrittura.
    Questi lock funzionano solo tra processi che cooperano, ovvero che cercano di
    effettuare un lock prima di cercare di scrivere.
    Provare ad effettuare una scrittura sul file tramite un processo standard
    (ad es. echo ciao > nomefile) mentre il lock e' detenuto da questo programma...
 ESERCIZIO: per fare i lock mandatory occorre montare un filesystem in modo che lo
 supporti. Usando il man mount e quanto mostrato in lezione 3, provare a vedere
 se echo ciao > nomefile si blocca su un filesystem con mandatory locking. */

 printf ("locked; hit Enter to unlock... ");
 /* Wait for the user to hit Enter. */
 getchar ();

 printf ("unlocking\n");
 /* Release the lock. */
 lock.l_type = F_UNLCK;
 fcntl (fd, F_SETLKW, &lock);
 /* qui manca il controllo dell'errore: aggiungerlo! */

 close (fd);
 return 0;
}

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

/* ESERCIZIO: mostrare che, se si apre chroot.c con il path assoluto, la open fallisce
   dopo la chiamata a chroot.
   Usare la variabile d'ambiente PWD per ottenere la directory corrente (vedere lezione 23).
   Verificare con valgrind --leak-check=full che non ci siano leak di memoria */

int main()
{
  int fd = open("chroot.c", O_RDONLY);
  if (fd < 0) {
    perror("Unable to open chroot.c");
  }
  else
    close(fd);
  if (chroot("../")) {
    perror("Unable to change dir");
    exit(2);
  }
  fd = open("chroot.c", O_RDONLY);
  if (fd < 0) {
    perror("Unable to open chroot.c after chroot");
  }
  else
    close(fd);
}

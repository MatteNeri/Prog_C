#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

/* ESERCIZIO: mostrare che, se si apre chdir.c con il path assoluto, la open non fallisce,
   neanche dopo la chiamata a chdir.
   Usare la variabile d'ambiente PWD per ottenere la directory corrente (vedere lezione 23).
   Verificare con valgrind --leak-check=full che non ci siano leak di memoria */

int main()
{
  int fd = open("chdir.c", O_RDONLY);
  if (fd < 0) {
    perror("Unable to open chdir.c");
  }
  else
    close(fd);
  if (chdir("../")) {
    perror("Unable to change dir");
    exit(2);
  }
  fd = open("esempi19/chdir.c", O_RDONLY);
  if (fd < 0) {
    perror("Unable to open chdir.c after chdir");
  }
  else
    close(fd);
}

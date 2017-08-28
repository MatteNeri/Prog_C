#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/vt.h>
#include <linux/kd.h>

/*
  ioctl e' la syscall di piu' basso livello tra quelle che consideriamo qui.
  Il suo uso e' complicato, perche' ci si puo' fare praticamente di tutto ma
  dipende fortemente dal file sul quale si effettuano le operazioni.
  Spesso e' usata nei driver di dispositivi.
  Concettualmente e' molto simile a fnctl, ed in effetti alcune operazioni
  di ioctl sono in realta' realizzate con un fcntl.
  Per far funzionare questo programma, mettersi su una console virtuale, ad
  esempio la seconda console virtuale premendo CTRL+ALT+F2.
  Inoltre, occorre eseguire con sudo ./ioctl
*/

int main()
{
  int vfd, c, is_vt;
  char val;
  struct vt_mode vtm;
  /* /dev/console e' un file speciale che punta alla console attualmente aperta
   (quella sulla quale si sta per digitare il comando sudo ./ioctl) */
  if (vfd = open("/dev/console", O_RDWR) < 0) {
    perror("vlock: could not open /dev/console");
    exit (1);
  }
  /* il comando VT_GETMODE chiede di mettere nella struttura puntata da vtm le informazioni
   sulla console virtuale */
  c = ioctl(vfd, VT_GETMODE, &vtm);
  if (c < 0) {
  /* se si prova ad invocare sudo ./ioctl da una console non virtuale (ad esempio,
   da un terminale come Terminal), questo ioctl  */
    perror("This tty is not a virtual console");
    close(vfd);
    return 1;
  }
  /* stampa dei principali campi di vtm appena settati */
  fprintf(stdout, "%x\n%x\n%d\n%d\n", vtm.mode, vtm.waitv, vtm.relsig, vtm.acqsig);
 /* char  mode;    /\* vt mode *\/ */
 /*    char  waitv;   /\* if set, hang on writes if not active *\/ */
 /*    short relsig;  /\* signal to raise on release req *\/ */
 /*    short acqsig;  /\* signal to raise on acquisition *\/ */
  /* mette in is_vt il numero della prima virtual console libera (normalmente, l'ottava,
   dato che tutte le altre sono gia' "occupate" da richieste di login */
  c = ioctl(vfd, VT_OPENQRY, &is_vt);
  if (c < 0) {
    perror("Unable to find free virtual console");
    close(vfd);
    return 1;
  }
  printf("%d\n", is_vt);
  /* vai alla prima console */
  c = ioctl(vfd, VT_ACTIVATE, 1);
  if (c < 0) {
    perror("Unable to switch to vt");
    close(vfd);
    return 1;
  }
  close(vfd);
  return 0;
}

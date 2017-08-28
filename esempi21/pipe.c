/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 ***************************************************************************** 
 MODULE: pipe.c
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

/* Tipico uso delle pipe: per la comunicazione tra padre e figlio */

/* ESERCIZIO: aggiungere i controlli mancanti sugli errori delle syscall */

/* ESERCIZIO: modificare questo programma in modo che legga un intero da riga di comando,
   il padre lo scriva sulla pipe, e il figlio stampi su stdout quanto letto dalla pipe
   aumentato di 1; stare attenti a non creare zombie */

/* ESERCIZIO: scrivere un programma in cui il padre manda continuamente un intero ed
   un double al figlio, che gli risponde con la somma (come double, ovviamente). Ad ogni
   ricezione della somma, il padre scrive tale risultato su stdout. Se la somma
   risulta essere zero, il figlio, anziche' mandare la somma sulla pipe, deve mandare
   SIGCHLD al padre e terminare con exit status pari ad n, se n e' il numero delle somme
   calcolate; il padre deve scrivere n prima di terminare a sua volta. */

int main(void)
{
  int     fd[2], nbytes;
  pid_t   childpid;
  char    string[] = "Hello, world!\n";
  char    readbuffer[80];

  pipe(fd);
        
  if((childpid = fork()) == -1)
    {
      perror("fork");
      exit(1);
    }

  if(childpid == 0)
    {
      /* Child process closes up input side of pipe */
      /* ESERCIZIO: mostrare che e' possibile invertire i ruoli (il figlio legge,
	 il padre scrive) */
      close(fd[0]);

      /* Send "string" through the output side of pipe */
      printf("Sending: %s\n", string);
      write(fd[1], string, (strlen(string)+1));
      exit(0);
    }
  else
    {
      /* Parent process closes up output side of pipe */
      close(fd[1]);

      printf("Receiving\n", string);
      /* Read in a string from the pipe */
      /* qualora lo scheduler mandasse in esecuzione il padre con la read prima che la write
	 del figlio sia completa, il padre si bloccherebbe fino a che il figlio non fa la
	 write */
      /* se non si e' attenti a mettere una write in corrispondenza di ogni read, si corre
	 il rischio di bloccare indefinitamente un processo */
      /* ESERCIZIO: verificare cosa succede se la pipe viene aperta in modalita' non
	 bloccante */
      nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
      printf("Received string: %s", readbuffer);
    }
        
  return(0);
}

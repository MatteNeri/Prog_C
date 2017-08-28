#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/* versione semplificata di dup2.c, in cui si usa la syscall dup2 anziche' la dup. Ci pensa dup2 a chiudere lo stdout che le viene passato come secondo argomento, prima di duplicarlo. */

int main()
{
  //First, we're going to open a file
  int file = open("myfile.txt", O_APPEND | O_WRONLY); /* attenzione, non c'e' O_CREAT... vedere le conseguenze */
  if(file < 0)    return 1;
 
  //Now we redirect standard output to the file using dup2
  if(dup2(file,1) < 0)    return 1;
 
  //Now standard out has been redirected, we can write to
  // the file
  printf("This will print in myfile.txt\n"); 
 
  return 0;
}

/* ESERCIZIO: fare lo stesso con lo stdin e lo stderr, non che' con un altro file diverso da myfile.txt */

#include <stdio.h>
#include <stdlib.h>

/* ESERCIZIO: provare a cambiare le 3 variabili usate qui, sia facendo in modo che
   il cambiamento sia permanente, sia facendo in modo che sia temporaneo a questo
   programma */

/*
  lanciarlo in due modi:

  ./getenv

  e

  key1=val1 ./getenv
 */

int main ()
{
   printf("PATH : %s\n", getenv("PATH"));
   printf("HOME : %s\n", getenv("HOME"));
   printf("key1 : %s\n", getenv("key1"));

   return(0);
}

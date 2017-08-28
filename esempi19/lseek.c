#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>

#define BUFF_SIZE 32

int main()
{
        int file=0;
	/* ESERCIZIO: aggiungere delle opportune perror */
        if((file=open("testfile.txt",O_RDONLY)) < -1)
                return 1;
 
        char buffer[BUFF_SIZE] =  {0};
        if(read(file,buffer,BUFF_SIZE - 1) != BUFF_SIZE - 1)  return 1;
	/* ESERCIZIO: che istruzione manca? */
        printf("%s\n",buffer);
 
        if(lseek(file,2,SEEK_SET) < 0) return 1;
	/* ESERCIZIO: fare in modo che il secondo ed il terzo argomento di lseek siano dati da riga di comando. Dopodiche', lanciare il programma 3 volte: 1) con questo attuale comportamento; 2) anziche' spostarsi al secondo byte del file, spostarsi indietro di 5 bytes rispetto all'attuale posizione; 3) anziche' spostarsi al secondo byte del file, spostarsi indietro di 5 bytes rispetto alla fine del file. Ci sono sempre 2 stampe come risultato? */
 
        if(read(file,buffer,BUFF_SIZE - 1) != BUFF_SIZE - 1)  return 1;
        printf("%s\n",buffer);
 
        return 0;
}

/*Implementazione di una "find" semplificata, gli argomenti vengono passati
separati da spazi */
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

#define LENGHT 100 // lunghezza della pila(iniziale)

int main(int argc, char const *argv[]) {
  int maxDepth = NULL; // scende al massimo di N livelli di directory
  //TEST
  int type; // tipo di file, o d->directory o f->regular file
  int gtsize; // file con dimensioni maggiori di gtsize
  int attrib; // controlla se il file ha setuit(0), setgid(1), sticky bit(2) o tutti e tre(3)
  //AZIONI
  int print; // true. Stampa il nome intero del file seguito da una new line
  int delete; // cancella il file, se è possibile


  DIR* dp = opendir(".");
  struct dirent* dir = readdir(dp);
  while(dir != NULL){
    printf("%s\n", dir->d_name);
    dir = readdir(dp);
  }

  char buf[500];
  getcwd(buf, 500);
  printf("%s\n", buf);
  return 0;
}

/*
void find(char[] dir, char[] file){

}*/

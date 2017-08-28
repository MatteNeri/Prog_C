#include <stdio.h>

/* ESERCIZIO: far si' che questo programma prenda un certo numero di argomenti,
   e che se tali argomenti compaiono nell'ambiente come nomi di variabili, allora
   non vengano scritti su stdout */

int main(int argc, char **argv, char **envp)
{
  /* envp e' un array di char *; dopo l'ultimo char * "effettivo" (ovvero contenente
     un assegnamento var=valore) ce n'e' uno ulteriore, che e' tutto a 0 (NULL). Questo in realta' succede anche per argv, ma li' solitamente
  non viene usato perche' c'e' argc... */
  while(*envp) { /* sfruttando quanto detto sopra, questo while va avanti fintantoche'
		    trova l'attuale puntatore e' var=valore */
    printf("%s\n",*envp);
    envp++;
  }
  /* ESERCIZIO: fare un secondo while con la stessa semantica di quello di sopra
     (quindi, deve stampare gli assegnamenti var=valore nell'ambiente).
     Verificare che effettivamente ogni variabile sia stampata 2 volte */
  return 0;
}

/* stampa una tebella con temperature fahrenheit e celsius,
utilizza delle variabili statiche */
#include <stdio.h>

#define LOWER 0 /*limite inferiore della tabella*/
#define UPPER 300 /*limite superiore della tabella*/
#define STEP 20 /*valore aggiunto ad ogni passo*/

main(){
  int fahr;
  for (fahr=LOWER; fahr<=UPPER; fahr=fahr+STEP){
    printf("%3d %6.1f\n", fahr, 5.0/9.0*(fahr-32));
  }
}

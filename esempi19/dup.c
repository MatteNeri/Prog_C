#include <unistd.h> /*Included for dup(2) and write(2)*/
 
#include <stdlib.h> /*Included for exit(3)*/
 
#define MESSAGE "Hey! Who redirected me?\r\n\0"
 
int main() {
    int newfd = dup(STDIN_FILENO); /* tutto quello che si fa su newfd avra' effetto su stdout */
    char buff[] = MESSAGE;
 
    if (newfd < 0) { /* aggiungere una perror */
        exit(EXIT_FAILURE);
    }
    else if (write(newfd, buff, sizeof(buff)) < 0) { /* la write su newfd ha l'effetto di scrivere su stdout (che e' gia' aperto per tutti i processi, non serve la open) */
        exit(EXIT_FAILURE);
    }

    /* ESERCIZIO: fare la stessa cosa con lo stdin */
 
    return EXIT_SUCCESS;
}

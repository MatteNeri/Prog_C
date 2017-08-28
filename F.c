/* Stampa i gradi Celsius e i Fahrenheit corrispondenti
	da lower fino a upper */
#include <stdio.h>
main(){

float cel, fahr;
int upper, lower, step;

lower = 0;
upper = 300;
step = 20;

fahr = lower;
printf("%3s %4s\n", "fahr", "cels");
while (fahr <= upper){
	cel = 5.0/9.0*(fahr-32);
	printf("%3.0f %6.1f\n",fahr, cel);
	fahr = fahr + step;
	}
}

#include <stdio.h>

int main(){
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;
	
	celsius = lower;
	
	printf("Temperature conversion\n");
	printf("celsius\tfahr\n");
	while(celsius <= upper){
		fahr = (celsius * 9.0/5.0) + 32.0;
		printf("%5.0f %6.1f\n",celsius,fahr);
		celsius = celsius + step;
	}
}

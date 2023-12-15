#include <stdio.h>

float fahrtocelsius(float fahr){
	return (5.0/9.0) * (fahr - 32.0);
}

int main(){
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;
	fahr = lower;
	
	printf("Temperature conversion\n");
	printf("Fahr\tcelsius\n");
	while(fahr <= upper){
		celsius = fahrtocelsius(fahr);
		printf("%4.0f %6.1f\n",fahr,celsius);
		fahr = fahr + step;
	}
}

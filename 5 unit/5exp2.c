#include <stdio.h>
#include <ctype.h>
#define SIZE 100

int bufp = 0;
int buf[SIZE];

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= SIZE){
		printf("Maximum size exceeded\n");
	}
	else{
		buf[bufp++] = c;
	}
}

int getfloat(double *pn){
	int c,sign;
	int power = 1;

	while(isspace(c = getch()))
			;
	if(!isdigit(c) && c!=EOF && c!='+' && c!='-' && c!='.'){
		ungetch(c);
		return -1;
	}

	if(c == EOF){
		return c;
	}

	sign = (c == '-') ? -1 : 1;

	if( c == '+' || c=='-')
		c = getch();

	if(!isdigit(c) &&  c!='.'){
		return 0;
	}

	for(*pn = 0 ; isdigit(c) ;  c = getch() )
		*pn = 10 * *pn + (c-'0');
	
	if(c=='.')
		c = getch();

	for(power = 1;isdigit(c); c = getch()){
		*pn = 10 * *pn + (c-'0');
		power = power * 10;
	}

	*pn *= sign;
	*pn = *pn / power;

	if(c != EOF)
		ungetch(c);
	return c;
}


int main(){
	int n ; 
	double  array[SIZE]={0};

	for(n = 0;n<SIZE && getfloat(&array[n]) != EOF ;){
		if(array[n]){
			n++;
		}
	}
	printf("Stored numbers:\n");
	for(int i=0;i<n;i++){
		printf("%lf ",array[i]);
	}
	printf("\n");
	return 0;
}


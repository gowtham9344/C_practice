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

int getint(int *pn){
	int c,sign;

	while(isspace(c = getch()))
			;
	if(!isdigit(c) && c!=EOF && c!='+' && c!='-'){
		ungetch(c);
		return -1;
	}

	if(c == EOF){
		return c;
	}

	sign = (c == '-') ? -1 : 1;

	if( c == '+' || c=='-')
		c = getch();

	if(!isdigit(c)){
		return 0;
	}

	for(*pn = 0 ; isdigit(c) ;  c = getch() )
		*pn = 10 * *pn + (c-'0');
	*pn *= sign;

	if(c != EOF)
		ungetch(c);
	return c;
}


int main(){
	int n, array[SIZE]={0};

	for(n = 0;n<SIZE && getint(&array[n]) != EOF ;){
		if(array[n]){
			n++;
		}
	}
	printf("Stored numbers:\n");
	for(int i=0;i<n;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
	return 0;
}


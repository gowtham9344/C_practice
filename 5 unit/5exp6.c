#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define MAXLINE 1000

int getop(char[]);
void push(double);
double pop(void);	

void reverse(char* s){
	int i = strlen(s) - 1;
	char* t = s+i;
	int c;

	while(s < t){
		c = *s;
		*s = *t;
		*t = c;	
		s++;
		t--;
	}
	
}

void itoa1(int n,char *s){
	int sign;
	char * t = s;

	if((sign = n ) < 0)
		n = -n;
	
	do{
		*s++ = n % 10 + '0';
	}while((n /= 10) > 0);

	if(sign < 0)
		*s++ = '-';
	*s = '\0';
	reverse(t);
}

int atoi1(char *s){
	int n ,sign;

	while(isspace(*s)){
		s++;
	}
	sign = (*s == '-') ? -1 : 1;
	if(*s == '+' || *s == '-')
		s++;
	for(n = 0;isdigit(*s);){
		n = 10 * n + (*s - '0');
		s++;
	}
	return sign * n;
}

int strindex(char *s,char *t){
	char *z = s;
	for(;*s != '\0';s++){
		char* r = s;
		char* w = t;
		for(;*w !='\0' && *r == *w ; r++ , w++)
			;
		if(*w == '\0'){
			return s-z; 
		}
	}
	return -1;
}


int main(){
	int type;
	double op2;
	char s[MAXOP];
	char m[MAXOP];
	double num = 0.0;
	printf("Enter a string to convert to number:");
	scanf("%s",s);
	printf("Converted string to number is %d\n",atoi1(s));
	itoa1(atoi1(s),s);
	printf("COnverted number to string  is %s\n",s);
	printf("Enter two strings for searching:\n");
	scanf("%s",s);
	scanf("%s",m);
	printf("The first occurence of the string is %d\n",strindex(s,m));
	printf("Give inputs for calculator in reverse polish notation\n");
	getchar();
	while((type = getop(s)) !=EOF){
		num = 0.0;
		op2 = 0.0;
		switch(type){
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
                                break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if(op2 != 0.0)
					push(pop() / op2);
				else
					printf("error : zero divisor\n");
				break;
			case '%':
				op2 = pop();
				if(op2 != 0.0){
					num = pop();
					if(num < 0.0 && op2 > 0.0){
						num = -num;
						push(fmod((op2 - fmod(num,op2)),op2));
					}
					else if (num > 0.0 && op2 < 0.0){
						op2 = -op2;
						push(-fmod((op2 - fmod(num,op2)),op2));
					}
					else if(num < 0.0 && op2 < 0.0){
						op2 = -op2;
						num = -num;
						push(-fmod(num , op2));
					}
					else{	       
						push(fmod(num , op2));
					}
				}
				else
					printf("error : zero divisor\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n",s);
				break;
			}
	}
	return 0;
}

int sp = 0;
double val[MAXVAL];

void push(double f){
	if(sp < MAXVAL)
		val[sp++] = f;
	else 
		printf("error : stack full , can't push %g\n",f);
}

double pop(void){
	if(sp > 0)
		return val[--sp];
	else{
		printf("error : stack empty\n");
		return 0.0;
	}
}

int li = 0;
char buf[MAXLINE];

int getline1(char[],int);


int getop(char *s){
	int c;


	if(buf[li] == '\0'){
		if(getline1(buf,MAXLINE)==0){
			return EOF;
		}
		else{
			li = 0;
		}	
	}

	while((*s = c = buf[li++]) == ' ' || c == '\t' )
		;
	*(s+1) = '\0';

	if(!isdigit(c) && c!='.' && c!='-')
		return c;
	if(isdigit(c) || c == '-')
		while(isdigit(*(++s) = c = buf[li++]))
			;
	if(c == '.')
		while(isdigit(*(++s) = c = buf[li++]))
			;
	*(s) = '\0';
		
	li--;

	if(*(s-1)=='-' && *s == '\0')
		return '-';
	return NUMBER;
}



int getline1(char *s, int lim) {
    int c;
    char *t = s;

    while (--lim > 0  && (c = getchar()) != EOF && c!='\n')
    {
        * s = c;
	s++;
    }
    if (c == '\n'){
        *s = c;
	s++;
    }
    *s = '\0';
    return s-t;
}


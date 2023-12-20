#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

int getop(char[]);
void push(double);
double pop(void);
double top(void);
void clear(void);
void duplicate(void);
void swap(void);

int powerfunc(int base, int times){
	int answer,i;
	answer = 1;
	i = 0;
	while(i<times){
		answer = answer * base;
		i++;
	}
	return answer;
}

double atof1(char s[]){
	double val,power,exp;
	int i,sign,expsign;

	for (i = 0;isspace(s[i]);i++);

	sign = (s[i] == '-') ? -1 : 1;

	if(s[i] == '+' || s[i] == '-')
		i++;
	for(val = 0.0 ; isdigit(s[i]);i++)
		val = 10.0 * val + (s[i] - '0');
	if(s[i] == '.')
		i++;
	for(power = 1.0 ; isdigit(s[i]);i++)
	{
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	if(s[i] == 'e' || s[i] == 'E'){
		i++;
	}
	if(s[i] == '-'){
		expsign = -1;
		i++;
	}
	else if(s[i] == '+'){
		expsign = 1;
	}
	else{
		expsign = 1;
	}

	for(exp = 0;isdigit(s[i]);i++){
		exp = exp * 10 + (s[i] - '0');
	}
	if(expsign == -1){
		return ((sign * val / power ) / powerfunc(10,exp));
	}
	return (( sign * val / power ) * powerfunc(10,exp));
}



int main(){
	int type;
	double op2;
	char s[MAXOP];
	double num = 0.0;

	while((type = getop(s)) !=EOF){
		num = 0.0;
		op2 = 0.0;
		switch(type){
			case NUMBER:
				push(atof1(s));
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
			case 'd':
				duplicate();
				break;
			case 's':
				swap();
				break;
			case 'c':
				clear();
				break;
			case 't':
				printf("%lf",top());
				break;
			case '\n':
				//printf("\t%.8g\n", pop());
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

double top(void){
	if(sp > 0)
		return val[sp-1];
	else{
		printf("error: stack empty\n");
		return 0.0;
	}
}

void duplicate(void){
	double num = top();
	if(sp < MAXVAL)
                val[sp++] = num;
        else
                printf("error : stack full , can't duplicate %g\n",num);
}

void swap(void){
	double num1 = pop();
	double num2 = pop();
	push(num1);
	push(num2);
}

void clear(void){
	sp = 0;
}

int getch(void);
void ungetch(int);

int getop(char s[]){
	int i = 0,c;

	while((s[0] = c = getch()) == ' ' || c == '\t' )
		;
	s[1] = '\0';

	if(!isdigit(c) && c!='.' && c!='-')
		return c;
	
	i = 0;
	if(isdigit(c) || c == '-')
		while(isdigit(s[++i] = c = getch()))
			;
	if(c == '.')
		while(isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if(c != EOF)
		ungetch(c);
	if(s[0]=='-' && s[1] == '\0')
		return '-';
	return NUMBER;
}

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("ungetch : too many characters\n");
	else
		buf[bufp++] = c;
}


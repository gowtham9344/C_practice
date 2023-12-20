#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define MAXLINE 1000

int getop(char[]);
void push(double);
double pop(void);	

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


int getop(char s[]){
	int i = 0,c;


	if(buf[li] == '\0'){
		if(getline1(buf,MAXLINE)==0){
			return EOF;
		}
		else{
			li = 0;
		}	
	}

	while((s[0] = c = buf[li++]) == ' ' || c == '\t' )
		;
	s[1] = '\0';

	if(!isdigit(c) && c!='.' && c!='-')
		return c;
	
	i = 0;
	if(isdigit(c) || c == '-')
		while(isdigit(s[++i] = c = buf[li++]))
			;
	if(c == '.')
		while(isdigit(s[++i] = c = buf[li++]))
			;
	s[i] = '\0';
		
	li--;

	if(s[0]=='-' && s[1] == '\0')
		return '-';
	return NUMBER;
}

int getline1(char s[], int lim) {
    int i, c;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c!='\n'; ++i)
    {
        s[i] = c;
    }
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}


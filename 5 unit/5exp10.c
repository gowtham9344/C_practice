#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFSIZE 100

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



int main(int argc, char* argv[]){
	int type;
	double op2;
	char s[MAXOP];
	double num = 0.0;
	

	for(int i=1; i<argc;i++){
		type = NUMBER;
		if(argv[i][0] >= '0' && argv[i][0] <='9'){
			type = NUMBER;	
		}
		else if(argv[i][0] =='-' && argv[i][1] >='0' && argv[i][1]<='9'){
			type = NUMBER;
		}
		else{
			type = argv[i][0];
		}

		if((type) !=EOF){
			num = 0.0;
			op2 = 0.0;
			switch(type){
				case NUMBER:
					push(atof1(argv[i]));
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
				case 't':
					printf("\t%.8g\n", pop());
					break;
				default:
					printf("error: unknown command %s\n",s);
					break;
				}
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


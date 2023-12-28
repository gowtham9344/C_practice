#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 10000
enum {NAME , PARENS , BRACKETS};
enum { NO, YES};

int tokentype;
char token[100]; 
char name[100];
char out[100];
int prevtoken = NO;
char datatype[100];
int bufp = 0;
int buf[SIZE];

void dcl(void);

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


void errormessage(char* msg){
	printf("%s",msg);
	prevtoken = YES;
}

int gettoken(void){
	int c;
	char *p = token;
	if(prevtoken == YES){
		prevtoken = NO;
		return tokentype;	
	}
		
	while((c = getch()) == ' ' || c == '\t');

	if(c == '('){
		if((c = getch()) == ')'){
			strcpy(token,"()");
			return tokentype = PARENS;		
		}
		else{
			ungetch(c);
			return tokentype = '(';
		}
	}else if(c == '['){
		for(*p++ = c ; *p!=']';){
			*p = getch();
			if(*p != ']'){
				if(*p == '\n' || *p == ')' || *p == '('){
					printf("error missing ]\n");
					ungetch(*p);
					*p = ']';
				}
				else
					*p++;			
			}
			
		}
		*(++p) = '\0';
		return tokentype = BRACKETS;
	}
	else if(isalpha(c)){
		for(*p++ = c ; isalnum(c = getch());)
			*p++ = c;
		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	else{
		return tokentype = c;	
	}
}


void dirdcl(void){
	int type;
	if(tokentype == '('){
		dcl();
		if(tokentype != ')')
			errormessage("error : missing brackets )\n");
		
	}
	else if(tokentype == NAME)
		strcpy(name,token);
	else
		errormessage("error : expected name or (dcl)\n");
	
	while((type = gettoken()) == PARENS|| type == BRACKETS){
		if(type == PARENS)
			strcat(out, "function returning ");
		else{
			strcat(out," array ");
			strcat(out,token);
			strcat(out," of ");		
		}
	}
}

void dcl(void){
	int ns;

	for (ns = 0;gettoken() == '*';)
		ns++;
	dirdcl();
	while(ns-- > 0){
		strcat(out," pointer to ");	
	}
}


int main(){
	while(gettoken() != EOF){
		strcpy(datatype , token);
		out[0] = '\0';
		dcl();
		if(tokentype != '\n')
			printf("syntax error\n");
		printf("%s: %s %s\n",name,out,datatype);
	}
	return 0;
}

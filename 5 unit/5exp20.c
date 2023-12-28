#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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


int typequal(void){
	static char* typeq[] = {
		"const",
		"volatile"	
	};
	char *pt = token;

	if(!(strcmp(typeq[0],pt) == 0 || strcmp(typeq[1],pt) == 0)){
		printf("hello\n");	
		return NO;
	}
	else
		return YES;
}

int typespec(void){
	static char* types[] = {
		"char",
		"int",
		"void"	
	};
        
	char *pt = token;
	if(!(strcmp(types[0],pt) == 0 || strcmp(types[1],pt) == 0 || strcmp(types[2],pt) == 0)){	
		return NO;
	}
	else
		return YES;
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

void dclspec(void){
	char temp[100];
	
	temp[0] = '\0';
	gettoken();

	do{
		if(tokentype != NAME){
			prevtoken = YES;
			dcl();
		}
		else if(typespec() == YES){
			strcat(temp," ");
			strcat(temp,token);
			gettoken();		
		}
		else if(typequal() == YES){
			strcat(temp," ");
			strcat(temp,token);
			gettoken();		
		}
		else{
			errormessage("unknown type in parameter list\n");
		}
	}while(tokentype != ',' && tokentype != ')');
	strcat(out,temp);
		
	if(tokentype == ',')
		strcat(out,",");
}

void parmdcl(void){
	do{
		dclspec();
	}while (tokentype == ',');
	if(tokentype !=')')
		errormessage("missing ) in parameter declaration\n");
}






void dirdcl(void){
	int type;

	if(tokentype == '('){
		dcl();
		if(tokentype != ')')
			errormessage("error : missing brackets )\n");
		
	}
	else if(tokentype == NAME){
		if(name[0] == '\0')
			strcpy(name,token);
	}
	else
		prevtoken = YES;
	
	while((type = gettoken()) == PARENS|| type == BRACKETS || type == '('){
		if(type == PARENS)
			strcat(out, "function returning ");
		else if(type == '('){
			strcat(out," function expecting ");
			parmdcl();
			strcat(out," and returning");
		}
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

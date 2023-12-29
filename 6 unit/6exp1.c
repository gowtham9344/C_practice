#include <stdio.h>
#include <ctype.h>
#define SIZE 10000

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

int getword(char* word,int lim){ 
	int c;
	char *w = word;
	
	while(isspace(c = getch()))
		;

	if(isalnum(c) || c == '_' || c == '#'){
		*w++ = c;
		for(;--lim > 0 ;w++){
			if(!isalnum(*w = getch()) && *w != '_'){
				ungetch(*w);
				break;		
			}
		}
	}
	else if(!isalpha(c)){
		if( c == '\"'){
			for(c = getch();c!='\"'; c = getch());		
		}
		else if(c == '/'){
			if((c = getch()) == '/'){
				for(c = getch();c!='\n'; c = getch());
			}
			else if(c == '*'){
				int t;
				for(c = getch(),t = getch(); c != '*' && t!='/';c = getch(),t = getch()){
					ungetch(t);				
				} 
			}
			else{
				ungetch(c);			
			}
		}
		*w = '\0';
		return c;	
	}
	
	
	*w = '\0';
	return word[0];
}

int main(){
	char words[100];
	getword(words,100);
	printf("%s\n",words);
}

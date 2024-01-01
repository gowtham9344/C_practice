#include <stdio.h>
#include <ctype.h>
#define MAXLINE 100
#define OCTLEN 6

int inc(int pos,int n){
	if(pos + n < MAXLINE){
		return pos + n;	
	}
	else{
		putchar('\n');
		return n;	
	}
}

int main(){

	int c,pos;
	pos = 0;

	while((c = getchar()) != EOF){
		if(iscntrl(c) || c == ' '){
				// non-graphic character 
			pos = inc(pos,OCTLEN);
			printf(" \\%03o ",c);
			
			if(c == '\n'){
				// graphic character 
				pos = 0;
				putchar('\n');
			}
		}
		else{
			pos = inc(pos,1);
			putchar(c);		
		}	
	}
}
	

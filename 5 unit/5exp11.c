#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 100
#define TAB 8

void detab();
void entab();
void settabstop(int argc,char* argv[],int tabstop[]);
int tabstop[MAXLINE+1] = {0};

int main(int argc,char* argv[])
{
	settabstop(argc,argv,tabstop);
	entab();	
}

void settabstop(int argc,char* argv[],int tabstop[]){
	if(argc == 1){
		int i = 0;
		while(i <= MAXLINE){
			if((i)%TAB == 0){
				tabstop[i] = 1;
			}
			else{
				tabstop[i] = 0;
			}
			i++;
		}
	}
	else{
		while(--argc){
			int placeOfInsert = atoi(argv[argc]);
			if(placeOfInsert > 0 && placeOfInsert <= MAXLINE)
				tabstop[placeOfInsert] = 1;
		}
	}
}

void detab(){
	int j = 1;
	int c = 0;
	while((c = getchar())!=EOF){
		if(c == '\t'){
			do{
				putchar(' ');	
			}while(!(tabstop[j++]));		
		}
		else if(c == '\n'){
			putchar(c);
			j = 1;
		}
		else{
			putchar(c);
			j++;
		}
	}	
}

void entab(){
	int c = 0;
	int j = 1;
	int numberOfBlanks = 0;
	int numberOfTabs = 0;
	
	while((c=getchar())!=EOF){
		if(c == ' '){
			if(!tabstop[j]){
				numberOfBlanks++;	
			}
			else{
				numberOfTabs++;
				numberOfBlanks = 0;
			}
			j++;
		}
		else
		{
			while(numberOfTabs-->0){
				putchar('\t');
			}
			numberOfTabs = 0;
			if(c == '\t'){
			       numberOfBlanks = 0;
			}

			while(numberOfBlanks-->0){
				putchar(' ');
			}
			numberOfBlanks = 0;
			putchar(c);
			if(c == '\n')
				j = 1;
			else if(c == '\t'){
				while(!tabstop[j]){
					j++;
				}
			}
			else
				j++;
		}
	}
}




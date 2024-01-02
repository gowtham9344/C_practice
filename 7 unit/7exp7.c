#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000


void findpattern(FILE* fp,char* fname, char* pattern,int except,int number){
	char line[MAXLINE];
	long lineno = 0;
	
	while(fgets(line,MAXLINE,fp) != NULL){
		++lineno;
		if((strstr(line,pattern) != NULL)!= except){
			if(*fname){
				printf("%s - ",fname);
			}
			if(number){
				printf("%ld: ",lineno);			
			}
			printf("%s",line);	
		}	
	}
}

int main(int argc,char* argv[]){
	
	char pattern[MAXLINE];
	int c,except = 0,number = 0;
		
	FILE* fp;
	
	while(--argc > 0 && (*++argv)[0] == '-'){
		while(c = *++argv[0]){
			switch(c){
				case 'x':
					except = 1;
					break;
				case 'n':
					number = 1;
					break;
				default:
					printf("find : illegal option %c\n",c);
					argc = 0;
					break;		
			}		
		}	
	}

	if(argc > 0){
		strcpy(pattern,*argv);	
	}
	else{
		printf("usage : find [-xn] pattern [file...] \n");
		exit(1);	
	}	
	
	if(argc == 1){
		findpattern(stdin,"",pattern,except,number);	
	}
	else{
		while(--argc > 0 ){
			if((fp = fopen(*++argv,"r")) == NULL){
				fprintf(stderr,"can't open file %s\n",*argv);
				exit(1);	
			}
			else{
				findpattern(fp,*argv,pattern,except,number);
				fclose(fp);		
			}		
		}	
	}
	return 0;
	
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

void filecompare(FILE* fp1,FILE* fp2){
	char line1[MAXLINE],line2[MAXLINE];

	char *lp1,*lp2;
	int flag = 0;

	do{
		lp1 = fgets(line1,MAXLINE,fp1);
		lp2 = fgets(line2,MAXLINE,fp2);
		
		if(lp1 == line1 && lp2 == line2){
			// lp1 and lp2 doesn't have null

			if(strcmp(line1,line2) != 0){
				flag = 1;
				printf("First difference in line\n%s\n",line1);
				lp1 = lp2 = NULL;
			}	
		}
		else if(lp1 != line1 && lp2 == line2){
			// lp1  have null
			flag = 1;
			printf("End of file in first file with line in second\n%s\n",line2);
		}
		else if(lp1 == line1 && lp2 != line2){
			// lp2  have null
			flag = 1;
			printf("End of file in second file with line in first\n%s\n",line1);
		}
	}while(lp1 == line1 && lp2 == line2);
	

	if(!flag){
		printf("There is no difference in two files\n");
	}
}


int main(int argc,char* argv[]){
	FILE* fp1,*fp2;
	if(argc != 3){
		fprintf(stderr,"Two files should be needed for comparing\n");	
		exit(1);
	}else{
		if((fp1 = fopen(*++argv,"r")) == NULL){
			fprintf(stderr,"can't open file 1 named %s\n",*argv);	
			exit(1);		
		}
		else if((fp2 = fopen(*++argv,"r")) == NULL){
			fprintf(stderr,"can't open file 2 named %s\n",*argv);	
			exit(1);		
		}
		else{
			filecompare(fp1,fp2);
			fclose(fp1);
			fclose(fp2);
			exit(0);		
		}
	}
	
	
}

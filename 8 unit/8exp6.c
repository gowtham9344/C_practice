#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void* calloc1(unsigned n,unsigned size){
	unsigned i,nb;
	char* p,*q;
	
	nb = n * size;
	if((p = q = malloc(nb)) != NULL){
		for(i =0 ;i< nb; i++)
			*p++ = 0;	
	}
	return q;
}

int main(){
	int* p = NULL;
	int i =0;
	int n = 10;
	
	p = calloc1(10,sizeof(*p));
	
	if(p == NULL){
		printf("calloc can't able to allocate memory\n");	
	}
	else{
		for(i = 0; i< 10;i++){
			printf("%d",p[i]);					
		}	
		printf("\n");
		free(p);
	}
	return 0;
}



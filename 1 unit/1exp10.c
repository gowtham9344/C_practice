#include <stdio.h>

int main(){
	int c;
	while((c = getchar())!=EOF){
		if(c == '\t'){
			printf("\\t");
		}
		else if(c == '\b'){
			printf("\\b");
		}
		else if(c == '\\'){
			printf("\\\\");
		}
		else{
			printf("%c",c);
		}
	}
}

// t111 answer

/* 
	words which are separated by hypen;
	words which may contain multiple blank spaces 
*/


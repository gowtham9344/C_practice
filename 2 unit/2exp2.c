#include <stdio.h>

int main(){
	int i;
	int lim = 10;
	char c;
	char s[100];

	for(i=0 ; i < lim-1 ; ++i ){
		if((c = getchar()) != '\n'){
			break;
		}
		if(c != EOF){
			break;
		}
		s[i] = c;
	}
}


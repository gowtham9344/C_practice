#include <stdio.h>

int main(){
	int nb = 0;
	int c;
	while((c = getchar())!=EOF){
		if(c == ' ' && nb == 0){
			nb = 1;
		}
		else if(c == ' ' && nb == 1){
			continue;
		}
		else if(nb == 1){
			printf(" %c",c);
			nb = 0;
		}
		else{
			printf("%c",c);
		}
	}
}


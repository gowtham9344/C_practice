#include <stdio.h>
#define IN 1
#define OUT 0

int main(){
	int c;
	int state = OUT;
	int wl = 0;
	int length[10] = {0};
	// assumption is word length should be less than 10

	while((c = getchar()) != EOF){
		if(c == ' ' || c == '\n' || c == '\t'){
			state = OUT;
			length[wl]++;
		}
		else if(state == OUT){
			wl = 0;
			state = IN;
		}
		if(state == IN){
			wl++;
		}
	}
	
	for(int i=1;i<=9;i++){
		printf("%d:",i);
		while(length[i]){
			printf("-");
			length[i]--;
		}
		printf("\n");
	}
}

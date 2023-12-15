#include <stdio.h>

int main(){
	int c;
	int length[128] = {0};

	while((c = getchar()) != EOF){
		length[c]++;
	}
	
	for(int i=0;i<=127;i++){
		printf("%c:",i);
		while(length[i]){
			printf("-");
			length[i]--;
		}
		printf("\n");
	}
}

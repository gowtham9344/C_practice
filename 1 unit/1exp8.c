#include <stdio.h>

int main(){	
	int nb = 0;
	int nt = 0;
	int nl = 0;
	int c;
	while((c = getchar())!=EOF){
		if(c == '\t'){
			nt++;
		}	
		else if(c == '\n'){
			nl++;
		}
		else if(c == ' '){
			nb++;
		}
	}
	printf("blank spaces = %d\n",nb);
	printf("tab spaces = %d\n",nt);
	printf("new lines = %d\n",nl);
}


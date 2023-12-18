#include <stdio.h>

char lower(char c){
	return c>='A' && c<='Z' ? c-'A'+'a' : c;
}

int main(){
	char ch;
	ch = getchar();
	printf("\nThe letter is %c\n",lower(ch));
}

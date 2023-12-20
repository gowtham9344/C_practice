#include <stdio.h>
#include <string.h>

char buf = 0;

int getch(void)
{
	if(buf > 0){
		char temp = buf;
		buf = 0;
		return temp;
	}
	else{
		return getchar();
	}	
}

void ungetch(int c){
	if(buf != 0)
		printf("ungetch : too many characters\n");
	else
		buf = c;
}

int main(){
	char c;
	c = getch();
	ungetch(c);
	printf("The undo getchar is %c\n",getch());
}

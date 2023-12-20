#include <stdio.h>
#include <string.h>
#define BUFSIZE 100

int buf[BUFSIZE];
int bufp = 0; 

// here we have to change the datatype of the buf array from the char to the int . this is because the EOF is literal which has the value of
// the value of -1

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE)
		printf("ungetch : too many characters\n");
	else
		buf[bufp++] = c;
}

int main(){
	int c;
	
	c = getch();
	ungetch(c);
	
	while((c = getch()) != EOF){
		putchar(c);
	}

}

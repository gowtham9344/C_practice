#include <stdio.h>
#include <string.h>
#define BUFSIZE 100
#define MAXLINE 1000

char buf[BUFSIZE];
int bufp = 0;

// we can use the ungetch in the ungets 
// ungets no need of the bufp and buf array 

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

void ungets(char s[]){
	int len = strlen(s);
	while(len--){
		ungetch(s[len]);
	}
}

int getline1(char s[], int lim) {
    int i, c;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF; ++i)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
}

int main(){
	char line[MAXLINE],c;
	getline1(line,MAXLINE);
	ungets(line);
	while((c = getch()) != EOF){
		putchar(c);
	}
}

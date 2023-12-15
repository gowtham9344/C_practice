#include <stdio.h>
#define MAXLINE 1000

int getline1(char line[], int maxline);


int main()
{
	int len;
	char line[MAXLINE];
	while ((len = getline1(line, MAXLINE)) > 0){
		if(len == 1 && line[len-1]=='\n'){
			continue;
		}
		printf("%d %s",len,line);
	}
	return 0;
}

int getline1(char s[],int lim)
{
	int c, i;
	for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	while(s[i-1]=='\t' || s[i-1]==' '){
		i--;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}




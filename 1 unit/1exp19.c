#include <stdio.h>
#define MAXLINE 1000

int getline1(char line[], int maxline);
void reverse(char line[],int len);


int main()
{
	int len;
	char line[MAXLINE];
	while ((len = getline1(line, MAXLINE)) > 0){
		reverse(line,len);
		printf("%s",line);
	}
	return 0;
}

int getline1(char s[],int lim)
{
	int c, i;
	for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void reverse(char s[],int len){
	if(s[len-1]=='\n'){
		len--;
	}
	int i = 0;
	int j = len-1;
	while(i<j){
		char r = s[i];
		s[i] = s[j];
		s[j] = r;
		i++;
		j--;
	}
}



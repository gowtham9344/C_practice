#include <stdio.h>
#define MAXLINE 1000

int getline1(char line[], int maxline);
void copy(char to[], char from[]);


int main()
{
	int len;
	int max;
	char line[MAXLINE];
	char longest[MAXLINE];
	char temp[MAXLINE];
	int templen = 0;
	int first = 0;
	max = 0;
	while ((len = getline1(line, MAXLINE)) > 0){
		if(first == 1 && len == MAXLINE-1 && line[MAXLINE-1]=='\0' && line[MAXLINE-2]!='\n'){
			templen += len;
			first = 1;
		}
		else if(len == MAXLINE-1 && line[MAXLINE-1]=='\0' && line[MAXLINE-2]!='\n'){
			copy(temp,line);
			templen = len;
			first = 1;
		}
		else if(first == 1 && len < MAXLINE-2){
			templen += len;
			first = 0;
		}
		else{
			templen = len;
			copy(temp,line);
		}
		
		if (templen > max) {
			max = templen;
			copy(longest, temp);
		}
		
	}
	if (max > 0) 
	printf("%d",max);
	printf("%s\n", longest);
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

void copy(char to[], char from[])
{
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0')
	++i;
}


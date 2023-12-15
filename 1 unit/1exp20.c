#include <stdio.h>
#define MAXLINE 1000
#define TAB 8

int getline1(char line[], int maxline);
void detab(char s[],char result[],int len);


int main()
{
	int len;
	char line[MAXLINE];
	char newline[MAXLINE];
	while ((len = getline1(line, MAXLINE)) > 0){
		detab(line,newline,len);
		printf("%s",newline);
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

void detab(char s[],char result[],int len){
	int old = 0;
	int new = 0;
	while(s[old] != '\0'){
		if(s[old]=='\t'){
			int tabstop = (new + TAB) / TAB;
			int spaces = tabstop * TAB - new;
			while(spaces--){
				result[new] = ' ';
				new++;
			}
			old++;
		}
		else{
		        result[new] = s[old];
			old++;
			new++;
		}
	}
	result[new]='\0';
}




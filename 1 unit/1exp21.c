#include <stdio.h>
#define MAXLINE 1000
#define TAB 8

int getline1(char line[], int maxline);
void entab(char s[],char result[],int len);


int main()
{
	int len;
	char line[MAXLINE];
	char newline[MAXLINE];
	while ((len = getline1(line, MAXLINE)) > 0){
		entab(line,newline,len);
		printf("%s",newline);
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

void entab(char s[],char result[],int len){
	int old = 0;
	int new = 0;
	while(s[old] != '\0'){
		if(s[old]==' '){
			int blankCount = 0;
			int requiredTab = 0;
			int requiredBlank = 0;
			while(s[old]!='\0' && s[old]==' '){
				blankCount++;
				old++;
			}
			int tabstop = (new + TAB) / TAB;
			int spaces = tabstop * TAB - new;
			if(blankCount >= spaces){
				blankCount = blankCount - spaces;
				requiredTab = 1;
			}
		
		
			while(blankCount >= TAB){
				blankCount -= TAB;
				requiredTab++;
			}
			
			requiredBlank = blankCount;
			
			while(requiredTab--){
				result[new] = '\t';
				new++;
			}
			while(requiredBlank--){
				result[new] = ' ';
				new++;
			}
		}
		else{
		        result[new] = s[old];
			old++;
			new++;
		}
	}
	result[new]='\0';
}




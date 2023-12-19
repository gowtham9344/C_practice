#include <stdio.h>
#define MAXLINE 1000

int getline1(char s[],int lim){
	int c,i;

	i = 0;
	while(--lim > 0 && (c = getchar()) != EOF && c!= '\n')
		s[i++] = c;
	if(c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int strrindex(char s[],char t[]){
	int i,j,k;
	int answer = -1;

	for (i = 0; s[i] !='\0' ;i++){
		for(j = i, k =0; t[k]!='\0' && s[j] == t[k];j++,k++)
			;
		if(k > 0 && t[k] == '\0')
			answer = i;
	}
	return answer;
}

int main(){
	char line[MAXLINE];
	char pattern[MAXLINE];

	printf("Enter the string:");
	scanf("%[^\n]s",line);
	getchar();
	printf("Enter the pattern:");
	scanf("%[^\n]s",pattern);
	printf("The answer is %d\n",strrindex(line,pattern));
}

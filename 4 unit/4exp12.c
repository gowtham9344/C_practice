#include <stdio.h>

void itoa1(char s[],int num){
	static int i=0;
	if(num < 0){
		s[i] = '-';
		(i)++;
		num = -num;	
	}

	if(num / 10){
		itoa1(s,num / 10);
	}
	s[i] = num%10 + '0';
	(i)++;
	s[i] = '\0';
}

int main(){
	int num = 0;
	char s[100];
	scanf("%d",&num);
	itoa1(s,num);
	printf("The converted number to string is %s\n",s);
}

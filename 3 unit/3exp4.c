#include <string.h>
#include <stdio.h>
#include <limits.h>
#define abs(x) ( (x) > 0 ? (x) : -(x))

//The problem occurs in the book is that when the negative value reaches the int_min then the corresponding positive is not available in the range of the signed integers so we cannot do directly.


void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

void itoa(int n,char s[]){
	int i,sign;

	sign = n;

	i = 0;

	do{

		s[i++] = abs(n%10)  + '0';
	}while((n /= 10) != 0);

	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int main(){
	int n = INT_MIN;
	char arr[100];
	itoa(n,arr);
	printf("%s\n",arr);
}	

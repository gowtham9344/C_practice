#include <string.h>
#include <stdio.h>
#include <limits.h>
#define abs(x) ( (x) > 0 ? (x) : -(x))


void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

void itob(int n,char s[],int b){
	int i,sign;

	sign = n;

	i = 0;

	do{
		int r = abs(n%b);
		s[i++] = r <='9' ? r + '0' : r + 'a';

	}while((n /= b) != 0);

	if(sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

int main(){
	int n = 0;
	int b = 0;
	printf("Enter base:");
	scanf("%d",&b);
	printf("Enter number:");
	scanf("%d",&n);
	char arr[100];
	itob(n,arr,b);
	printf("The answer is %s\n",arr);
}	

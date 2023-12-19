#include <string.h>
#include <stdio.h>
#include <limits.h>
#define abs(x) ( (x) > 0 ? (x) : -(x))

void reverse(char s[]) {
    int c, i, j;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
        c = s[i], s[i] = s[j], s[j] = c;
}

void itoa(int n,char s[],int spaces){
	int i,sign;

	sign = n;

	i = 0;

	do{

		s[i++] = abs(n%10)  + '0';
	}while((n /= 10) != 0);

	if(sign < 0)
		s[i++] = '-';
	
	while(i < spaces){
                s[i++] = ' ';
        }


	s[i] = '\0';
	reverse(s);
}

int main(){
	int n = INT_MIN;
	char arr[100];
	int spaces;
	printf("Enter Number:");
	scanf("%d",&n);
	printf("Enter spaces:");
	scanf("%d",&spaces);
	itoa(n,arr,spaces);
	printf("%s\n",arr);
}	

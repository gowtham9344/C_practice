#include <stdio.h>

int setbits(int x,int p,int n,int y){
	return x & ~(~(~0 << n) << (p+1-n))  | ((y & ~(~0 << n)) << (p+1-n));
}

int main(){
	int x;
	int p;
	int n;
	int y;
	printf("Enter X:");
	scanf("%d",&x);
	printf("Enter P:");
	scanf("%d",&p);
	printf("Enter N:");
	scanf("%d",&n);
	printf("Enter Y:");
	scanf("%d",&y);
	printf("Answer is %d\n",setbits(x,p,n,y));
}


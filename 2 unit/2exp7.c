#include <stdio.h>

int invert(int x,int p,int n){
	return x & ~(~(~0 << n) << (p+1-n))  | (((~(~0<<n)) << (p+1-n)) & ~(x & (~(~0 << n) << (p+1-n))));
}

int main(){
	int x;
	int p;
	int n;
	printf("Enter X:");
	scanf("%d",&x);
	printf("Enter P:");
	scanf("%d",&p);
	printf("Enter N:");
	scanf("%d",&n);
	printf("Answer is %d\n",invert(x,p,n));
}


#include <stdio.h>
#include <math.h>

unsigned int rightrot(int x,int n){
	int leftmost = (int)log2((unsigned int)~0) + 1;	
	int r = x & ~(~0 << n) ;
	unsigned int s = x >> n;
	s = s | r << (leftmost - n);
	return s;
}

int main(){
	int x = 0;
	int n = 0;
	scanf("%d",&x);
	scanf("%d",&n);
	printf("The right rotated number is %u\n",rightrot(x,n));
}
	

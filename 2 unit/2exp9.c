// this is because that the -1 always removes the last bit set either it is odd or even 
// in either case we do bitwise and for x and x-1 so only same bits that are included in both
// are proceeded. 

#include <stdio.h>

int bitcount(unsigned int num){
	int count = 0;

	while(num){
		num = num&num-1;
		count++;
	}
	return count;
}

int main(){
	unsigned int num;
	scanf("%u",&num);
	
	printf("The number of 1 bits in the %u are %d\n",num,bitcount(num));
}

#include <stdio.h>
#define swap(t,x,y) { \
	t z;\
	z = x;\
	x = y;\
	y = z;\
}


int main(){
	int x,y;
	x = 5;
	y = 10;
	swap(int,x,y);
	printf("x = %d, y = %d\n",x,y);
}


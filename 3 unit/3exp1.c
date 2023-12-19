#include <stdio.h>

// binary search with only one check in the if statement

int binsearch(int x,int v[],int n){
	int low,high,mid;

	low = 0;
	high = n - 1;
	mid = (low + high)/2;
	while(low <= high && x!=v[mid]){
		if(x  < v[mid]){
			high = mid - 1;
		}
		else{
			low = mid;
		}
		mid = (low + high)/2;
	}
	if(v[mid] == x){
		return mid;
	}
	return -1;
}

int main(){
	int arr[10] = {1 , 2 , 3, 4 , 6, 7 , 8, 9,10 , 11};
	printf("The answer is %d",binsearch(10,arr,10));
}

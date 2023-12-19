#include <stdio.h>

// binary search with only one check in the if statement

int binsearch(int x,int v[],int n){
	int low,high,mid;

	low = 0;
	high = n - 1;

	while(low <= high){
		mid = (low + high)/2;
		if(x  > v[mid]){
			low = mid + 1;
		}
		else{
			high = mid - 1;
		}
	}
	if(v[low] == x){
		return low;
	}
	return -1;
}

int main(){
	int arr[10] = {1 , 2 , 3, 4 , 6, 7 , 8, 9,10 , 11};
	printf("The answer is %d\n",binsearch(4,arr,10));
}

#include <stdio.h>

int strend(char* s,char* t){
	int len = 0;
	while(*s++);
	while(*t++){
		len++;
	}
	*s--;
	*t--;
	while(len-- && *s-- == *t--){
		//len--;
	}
	if(len > 0 && s == t){
		return 0;
	}
	return 1;
}

int main(){
	char arr[100];
	char arr1[100];

	scanf("%[^\n]s",arr);
	getchar();
	scanf("%[^\n]s",arr1);

	int r = strend(arr,arr1);
	printf("%d\n",r);
}


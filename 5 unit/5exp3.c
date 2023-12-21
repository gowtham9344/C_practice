#include <stdio.h>

void strcat(char* s,char* t){
	while(*s++ != '\0');
	s--;
	while(*s++ = *t++);
}

int main(){
	char arr[100];
	char arr1[100];

	scanf("%[^\n]s",arr);
	getchar();
	scanf("%[^\n]s",arr1);

	strcat(arr,arr1);
	printf("%s\n",arr);
}


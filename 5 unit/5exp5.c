#include <stdio.h>

int strncmp1(char* s,char* t,int n){
	int len = n;
	while(*s++ == *t++ && --len);

	if(len == 0){
		return 0;
	}

	t--;
	s--;
	return *s - *t;
}

void strncat1(char* s,char* t,int n){
	while(*s++ != '\0');
	s--;
	int len = n;
	while(len--){
		*s = *t;
	        s++;
		t++;	
	}
	*s = '\0';
}

void strncpy1(char* s,char* t,int n){
	int len = n;
	while(len--){
                *s = *t;
                s++;
                t++;
        }

	*s = '\0';
}

int main(){
	char arr[100];
	char arr1[100];

	scanf("%[^\n]s",arr);
	getchar();
	scanf("%[^\n]s",arr1);
	int n = 0;
	scanf("%d",&n);
	printf("The answer of strncmp is %d\n",strncmp1(arr,arr1,n));
	strncat1(arr,arr1,n);
	printf("concatenated %d characters is  %s\n",n,arr);
	strncpy1(arr,arr1,n);
	printf("The content copied %d characters is %s\n",n,arr);
}


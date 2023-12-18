#include <stdio.h>

int any(char str1[],char str2[]){
	char arr2[128] = {0};
	int i = 0;
	while(str2[i] != '\0' && str2[i] != '\n'){
		arr2[str2[i]]++;
		i++;
	}
	i = 0;
	while(str1[i] != '\0' && str1[i] != '\n'){
		if(arr2[str1[i]] != 0 ){
			return i;
		}
		i++;
	}
	return -1;
}

int main(){
	char str1[100];
	char str2[100];
	scanf("%s",str1);
	scanf("%s",str2);
	int answer = any(str1,str2);
	printf("position is %d\n",answer);
}


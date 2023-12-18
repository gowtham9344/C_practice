#include <stdio.h>

void squeeze(char str1[],char str2[]){
	char arr2[128] = {0};
	int i = 0;
	while(str2[i] != '\0' && str2[i] != '\n'){
		arr2[str2[i]]++;
		i++;
	}
	i = 0;
	int j = 0;
	while(str1[i] != '\0' && str1[i] != '\n'){
		if(arr2[str1[i]] == 0){
			str1[j++] = str1[i];
		}
		i++;
	}
	//j++;
	//j++;
	str1[j] = '\0';
}

int main(){
	char str1[100];
	char str2[100];
	scanf("%s",str1);
	scanf("%s",str2);
	squeeze(str1,str2);
	printf("%s\n",str1);
}


#include <stdio.h>

int htoi(char arr[]){
	int answer = 0 ;
	int i = 0;
	
	if(arr[i]=='0' && (arr[i+1]=='x' || arr[i+1]=='x')){
		i = 2;
	}

	while(arr[i] !='\0' && arr[i]!='\n'){
		answer = answer * 16;
		if(arr[i] >='0' && arr[i]<='9'){
			answer += arr[i]-'0';
		}
		else if(arr[i]>='a' && arr[i]<='f'){
			answer += arr[i]-'a' + 10;
		}
		else if(arr[i]>='A' && arr[i]<='F'){
			answer += arr[i]-'A' + 10;
		}
		i++;
	}
	return answer;
}

int main(){
	char arr[100];
	scanf("%s",arr);
	int answer = htoi(arr);
	printf("%d\n",answer);
}

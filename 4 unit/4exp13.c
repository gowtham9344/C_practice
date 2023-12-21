#include <stdio.h>
#include <string.h>

void reverse(char s[]){
	static int i = 0;
	static int j = 0;
	if(s[i] == '\0'){
		return;
	}
	char temp = s[i];
	i++;
	reverse(s);
	s[j] = temp;
	j++;
}

int main(){
	char s[100];
	scanf("%s",s);
	reverse(s);
	printf("The string is %s\n",s);
}

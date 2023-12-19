#include <stdio.h>
#define MAXLINE 1000

void getline1(char t[],int lim){
        int i = 0;
        char c;

        while(i<lim-1 && ((c = getchar())!=EOF)){
                t[i] = c;
                i++;
        }
        t[i] = '\0';
}

void expand(char s1[],char s2[]){
	int i = 0;
	int j = 0;
	char c;

	while((c = s1[i++]) != '\0'){
		if(s1[i]=='-' && s1[i+1] >= c){
			int k = c;
			while(k < s1[i+1]){
				s2[j] = k;
				k++;
				j++;	
			}
			i++;
		}
		else{
			s2[j] = c;
			j++;

		}
	}	
	j++;
	s2[j] = '\0';
}


int main(){
        char s[MAXLINE],t[MAXLINE];
        getline1(t,MAXLINE);
	expand(t,s);
	printf("%s\n",s);
}


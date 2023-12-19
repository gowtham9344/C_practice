#include <stdio.h>
#define MAXLINE 1000

void escape(char s[],char t[]){
	int i = 0;
	int j = 0;
	while(t[j]!='\0'){
		switch(t[j]){
			case '\n':
				s[i] = '\\';
				i++;
				s[i] = 'n';
				i++;
				break;
			case '\t':
				s[i] = '\\';
				i++;
				s[i] = 't';
				i++;
				break;
			default:
				s[i] = t[j];
				i++;
				break;
		}
		j++;
				
	}
	s[i] = '\0';
}

void rescape(char s[],char t[]){
        int i = 0;
        int j = 0;
        while(t[j]!='\0'){
                switch(t[j]){
                        case '\\':
                  		switch(t[j+1]){
					case 'n':
						s[i] = '\n';
						j++;
						i++;
						break;
					case 't':
						s[i] = '\t';
						i++;
						j++;
						break;
					default :
						s[i] = '\\';
						i++;
						break;
				}		
                                break;
                        default:
                                s[i] = t[j];
                                i++;
                                break;
                }
                j++;

        }
	s[i] = '\0';
}

void getline1(char t[],int lim){
	int i = 0;
	char c;

	while(i<lim-1 && ((c = getchar())!=EOF)){
		t[i] = c;
		i++;
	}
	t[i] = '\0';
}

int main(){
	char s[MAXLINE],t[MAXLINE];
	getline1(t,MAXLINE);
	escape(s,t);
	printf("The escape function output is\n%s\n", s);
	rescape(t,s);
	printf("The reverse escape function output is\n%s\n", t);
}

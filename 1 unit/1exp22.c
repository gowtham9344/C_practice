#include <stdio.h>
#include <string.h>
#define MAXLINE 1000
#define CUT 8

void splitprint();


int main()
{
	splitprint();
	return 0;
}


void splitprint(){
	int i=0;
	int blank = 0;
	char s[CUT+1];
	int blankindex = 0;
	char c;
	
	while((c=getchar())!=EOF){
		if(c=='\n'){
			blank = 0;
			s[i]='\0';
			printf("%s\n",s);
			i=0;
			continue;
		}
		s[i] = c;

		if(c==' ' || c=='\t'){
			blankindex = i;
			blank = 1;
		}
		
		if(i==CUT-1){
			if(blank){
				char d = s[blankindex+1];
				s[blankindex+1] = '\0';
				printf("%s\n",s);
				i = 0;
				s[i] = d;
				i = CUT - 1 - blankindex;
				memmove(s+1,s+blankindex+2,i);
				blank = 0;
				continue;
			}
			else{
				s[CUT] = '\0';
				printf("%s\n",s);
				blank = 0;
				i = 0;	
				continue;
			}
		}
		i++;
		
	}
}


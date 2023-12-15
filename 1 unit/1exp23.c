#include <stdio.h>

int main(){
	int state = 0;
	int state1 = 0;
	char c;
	while(!state && (c=getchar())!=EOF){
		if(c == '\"'){
			state1 = !state1;
			putchar('\"');
		}
		else if(state1 == 0 && c == '/'){
			char d = getchar();
			if(d == '/'){
				char h = getchar();
				if(h == EOF){
					break;
				}
				while(h!='\n'){
					h = getchar();
					if(h == EOF){
						state = 1;
						break;
					}
				}
				if(!state)
				putchar('\n');
			}
			else if(d == '*'){
				char h = getchar();
				if(h == EOF){
					break;
				}
				else{
					char j = getchar();
					if(j == EOF){
						break;
					}
					else{
						while(!(h=='*' && j=='/')){
							h = j;
							j = getchar();
							if(j == EOF){
								state = 1;
								break;
							}
						}
					}
				}
			}	
			else{
				putchar(c);
				if(d == EOF){
					break;
				}
				putchar(d);
				if(d == '\"'){
					state1 = !state1;
				}
						
			}
			
			
		}
		else{
			putchar(c);
		}
	}
}

#include <stdio.h>

int main(){
	int arr[200];
	int top = 0;
	int state1 = 0;
	int state = 0;
	int wrong = 0;
	char c;
	while(!state && (c=getchar())!=EOF){
		if(c == '\"'){
			state1 = !state1;
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
				if(d == EOF){
					break;
				}
				if(d == '\"'){
					state1 = !state1;
				}		
			}
			
			
		}
		if(state1 == 0 && c=='{'){
			arr[top] = '{';
			
			top++;
		}
		else if(state1 == 0 && c=='('){
			arr[top] = '(';
			top++;
		}
		else if(state1 == 0 && c=='['){
			arr[top] = '[';
			top++;;
		}
		else if(state1 == 0 && c==']'){
			top--;
			if(arr[top]!='['){
				printf("ERROR NO MATCHING FOR ]\n");
				wrong = 1;
				break;
			}
		}
		else if(state1 == 0 && c==')'){
			top--;
			if(arr[top]!='('){
				printf("ERROR NO MATCHING FOR )\n");
				wrong = 1;
				break;
			}
		}
		else if(state1 == 0 && c=='}'){
			top--;
			if(arr[top]!='{'){
				printf("ERROR NO MATCHING FOR }\n");
				wrong = 1;
				break;
			}
		}

	}
        if(wrong == 0 && top == 0){
		printf("ALL ARE MATCHING BRACKETS\n");
	}
	else if(wrong == 0 && top > 0){
		printf("ERROR DUE TO UNCLOSED BRACKETS\n");
	}
	
}

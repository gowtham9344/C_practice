#include <stdio.h>
#include <string.h>
#include <ctype.h>

// when compiling give name as lower or upper to see the result correctly

int main(int argc,char* argv[]){
	int c;
	if(strcmp(&(argv[0][2]),"lower") == 0){
		while((c = getchar()) != EOF)
			putchar(tolower(c));
	}
	else{
		while((c = getchar()) != EOF)
			putchar(toupper(c));	
	}
	
	return 0;
}

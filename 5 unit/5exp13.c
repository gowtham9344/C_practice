#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFAULT 10 // default lines printed
#define LINES 100 // max lines can be printed
#define MAXLEN 100 // maximum length of single line


int getline1(char *s, int lim) {
    int c;
    char *t = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;

    *s = '\0';
    return s - t;
}

int main(int argc,char* argv[]){
	int n; 

	if(argc == 1){
		n = DEFAULT;
	}
	else if(argc == 2 && (*++argv)[0] == '-'){
		n = atoi(argv[0]+1);
	}
	else{
		printf("Usage: tail [-n]\n");
		return 0;
	}
	
	if(n < 1 || n > LINES){
		n = LINES;
	}


	char* p;
	char* buff;
	char* buffend;
	char line[MAXLEN];
	char* lineptr[LINES];
	
	int start = 0;
	int end = 0;
	int count = 0;
	int len = 0;

	for(int i = 0;i<LINES ;i++){
		lineptr[i] = NULL;
	}
	
	if( (p = buff = (malloc(LINES * MAXLEN))) == NULL){
		printf("cannot able to allocate memory\n");
		return 0;
	}

	buffend = buff + LINES*MAXLEN;

	while((len = getline1(line,MAXLEN)) > 0){
		if(len + p + 1 >= buffend){
			p = buff;
		}
		lineptr[end] = p;
		strcpy(lineptr[end],line);
		end++;

		if(end >= LINES){
			end = 0;
		}

		p += len + 1;
		count++;
	}

	if( n > count){
		n = count;
	}

	start = end - n;

	if( start < 0){
		start = start + LINES;
	}

	for(int i = start ; n-- > 0 ; i = (i + 1)%LINES){
		printf("%s",lineptr[i]);
	}

}

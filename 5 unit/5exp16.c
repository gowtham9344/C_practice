#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define MAXBUFF 1000
#define MAXLEN 100
#define MAXLINES 100
char buff[MAXBUFF];
static char option = 0;

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


void swap(void *v[],int i,int j){
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

int numcmp(char* s1,char* s2){
	double v1,v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if(v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int charcmp(char* s1,char* s2){
	int f = option & 4;
	int d = option & 8;
	char com1,com2;

	do{
		if(d){
			while(!isalnum(*s1) && *s1 != ' ' && *s1 != '\0'){
				s1++;
			}
			while(!isalnum(*s2) && *s2 != ' ' && *s2 != '\0'){
                                s2++;
                        }

		}

		com1 = (f) ? tolower(*s1) : *s1;
                com2 = (f) ? tolower(*s2) : *s2;
                if(com2 == '\0' && com1 == '\0'){
                        return 0;
                }
		s1++;
		s2++;
	}while(com1 == com2);	

	return com1 - com2;
}

void qsort1(void *v[],int left,int right, int (*comp)(void *,void *))
{
	int i,last;
	void swap(void *v[],int,int);

	if(left >= right)
		return;
	swap(v,left,(left+right)/2);
	last = left;
	for(i = left + 1;i <= right;i++)
		if((*comp)(v[i],v[left]) < 0)
			swap(v,++left,i);
	swap(v,left,last);
	qsort1(v,left,last-1,comp);
	qsort1(v,last+1,right,comp);
}

int readlines(char *lineptr[], char *buff, int maxlines) {
    int len, nlines;
    char line[MAXLEN];
    char *p = buff;
    char *buffend = buff + MAXBUFF;

    nlines = 0;

    while ((len = getline1(line, MAXLEN)) > 0)
        if (nlines >= maxlines || p + len > buffend)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            p += len;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines,int decr) {
    if(!decr)
    	for (int i = 0; i < nlines; i++)
        	printf("%s\n", lineptr[i]);
    else
	for (int i = nlines-1; i >= 0; i--)
                printf("%s\n", lineptr[i]);
}

int main(int argc,char* argv[]) {
    int nlines;
    char* lineptr[MAXLINES];
    char c;
    int error = 0;
	
    while(--argc >0 && (*++argv)[0] == '-')
	    while(c = *++argv[0])
		    switch(c){
			    case 'n':
				    option = option | 1;
				    break;
			    case 'r':
				    option = option | 2;
				    break;
			    case 'f':
				    option = option | 4;
				    break;
		            case 'd':
				    option = option | 8;
				    break;
			    default:
				    printf("illegal option \n");
				    error = 1;
				    break;
		    }

    if(error){
	    printf("Usage: sort -n -r -f\n");
	    return -1;
    }
    else if ((nlines = readlines(lineptr, buff, MAXLINES)) >= 0) {

	if(option & 1)
        	qsort1((void **)lineptr, 0, nlines - 1,(int (*)(void *, void *)) numcmp);
	else
		qsort1((void **)lineptr, 0, nlines - 1,(int (*)(void *, void *)) charcmp);
        writelines(lineptr, nlines,option & 2);
        return 0;
    } else {
        printf("error: input too big to sort \n");
        return -1;
    }
}

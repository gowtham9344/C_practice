#include<stdio.h>
#include<string.h>
#define MAXLEN 1000
#define MAXLINES 5000
#define MAXBUFF 5000

// here i have created a buff and store those in the Main based on the space in
// buff i will allocate the space this will reduce a call to the alloc and it 
// corresponding unalloc procedures

char buff[MAXBUFF];

int readlines(char *lineptr[], char *buff, int maxlines);

void writelines(char *lineptr[], int nlines);

void qsort(char *v[], int left, int right);


int main(void) {
    int nlines;
    char* lineptr[MAXLINES];

    if ((nlines = readlines(lineptr, buff, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort \n");
        return 1;
    }
}


int getline1(char *, int);

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

void writelines(char *lineptr[], int nlines) {
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

void qsort(char *v[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);

    last = left;

    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


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

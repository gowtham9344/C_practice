#include <fcntl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

#ifdef NULL
#undef NULL
#endif

#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20


enum _flags {
    _READ = 01,  /* file open for reading */
    _WRITE = 02, /* file open for writing */
    _UNBUF = 03, /* file is unbuffered */
    _EOF = 010,  /* EOF has occurred on this file */
    _ERR = 020,  /* error occurred on this file */
};


typedef struct _iobuf {
    int cnt;    /* characters left */
    char *ptr;  /* next character position */
    char *base; /* location of the buffer */
    int flag;   /* mode of the file access */
    int fd;     /* file descriptor */
} FILE;

FILE _iob[OPEN_MAX] = {/* stdin, stdout, stderr */
        {0, (char *) 0, (char *) 0, _READ,           0},
        {0, (char *) 0, (char *) 0, _WRITE,          1},
        {0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}};



#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])


int _fillbuf(FILE *);

int _flushbuf(int, FILE *);

int fflush(FILE* fp);
int fclose(FILE* fp);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))

#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#define PERMS 0666


FILE *fopen(char *name, char *mode) {
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break; /* found free slot */

    if (fp >= _iob + OPEN_MAX) /* no free slots */
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);

    if (fd == -1) /* couldn't access name */
        return NULL;

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}


int _fillbuf(FILE *fp) {
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL) 
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }

    return (unsigned char) *fp->ptr++;
}

int _flushbuf(int x, FILE *fp){
	unsigned nc;
	int bufsize;

	if(fp < _iob || fp >= _iob + OPEN_MAX)
		return EOF;
	
	if((fp->flag & (_WRITE | _ERR)) != _WRITE){
		return EOF;	
	}
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	
	if(fp->base == NULL){
		if((fp->base = (char*) malloc(bufsize)) == NULL){
				fp->flag |= _ERR;
			return EOF;
		}	
	}
	else{
		nc = fp->ptr - fp->base;
		if(write(fp->fd,fp->base,nc)!=nc){
			fp->flag |= _ERR;
			return EOF;		
		}	
	}

	fp->ptr = fp->base;
	*fp->ptr++ = (char) x;
	fp->cnt = bufsize - 1;
	return x;
}


int fclose(FILE *fp){
	int rc;
	
	if((rc = fflush(fp)) != EOF){
		free(fp->base);
		fp->ptr = NULL;
		fp->cnt = 0;
		fp->base = NULL;
		fp->flag &= (_READ | _WRITE);
	}
	return rc;
}


int fflush(FILE* fp){
	int rc = 0;
	
	if(fp < _iob || fp >= _iob + OPEN_MAX)
		return EOF;
	if(fp->flag & _WRITE)
		rc = _flushbuf(0,fp);
	fp->ptr = fp->base;
	fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	return rc;
}

int main(int argc, char *argv[]) {
    int c;
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
}


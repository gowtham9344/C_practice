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

//The code size of the modified function was larger and the functions were slower.

struct flag_field{
	unsigned is_read : 1;
	unsigned is_write : 1;
	unsigned is_unbuf : 1;
	unsigned is_buf : 1;
	unsigned is_eof : 1;
	unsigned is_err : 1;
};

typedef struct _iobuf{
	int cnt;
	char* ptr;
	char* base;
	struct flag_field flag;
	int fd;
} FILE;

extern FILE _iob[OPEN_MAX];

FILE _iob[OPEN_MAX] = {/* stdin, stdout, stderr */
        {0, (char *) 0, (char *) 0, {1,0,0,0,0,0}, 0},
        {0, (char *) 0, (char *) 0, {0,1,0,0,0,0}, 1},
        {0, (char *) 0, (char *) 0, {0,1,1,0,0,0}, 2}};


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


FILE* fopen(char* name,char *mode){
	int fd;
	FILE *fp;
	
	if(*mode != 'r' && *mode != 'w' && *mode !='a'){
		return NULL;	
	}
	for(fp = _iob; fp <_iob + OPEN_MAX; fp++)
		if(fp->flag.is_read == 0 && fp->flag.is_write == 0)
			break;
	if(fp >= _iob + OPEN_MAX)
		return NULL;
	
	if(*mode == 'w')
		fd = creat(name,PERMS);
	else if(*mode == 'a'){
		if(fd = open(name,O_WRONLY,0))
			fd = creat(name,PERMS);
		lseek(fd,0L,2);	
	}
	else{
		fd = open(name,O_RDONLY,0);	
	}
	if(fd == -1){
		return NULL;
	}
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag.is_unbuf = 0;
	fp->flag.is_buf = 1;
	fp->flag.is_eof = 0;
	fp->flag.is_err = 0;
	if(*mode == 'r'){
		fp->flag.is_read = 1;
		fp->flag.is_write = 0;	
	}
	else{
		fp->flag.is_read = 0;
		fp->flag.is_write = 1;	
	}

	return fp;
}

int _fillbuf(FILE* fp){
	int bufsize;
		
	if(fp->flag.is_read == 0 || fp->flag.is_eof == 1 || fp->flag.is_err == 1)
		return EOF;
	bufsize = (fp->flag.is_unbuf == 1) ? 1 : BUFSIZ;
	if(fp->base == NULL)
		if((fp->base = (char*) malloc(bufsize)) == NULL)
			return EOF;
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd,fp->ptr,bufsize);
	
	if(--fp->cnt < 0){
		if(fp->cnt == -1){
			fp->flag.is_eof = 1;
		}
		else
			fp->flag.is_err = 1;
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
	
	if(fp->flag.is_write == 0 || fp->flag.is_err == 1){
		return EOF;	
	}
	
	bufsize = (fp->flag.is_unbuf) ? 1 : BUFSIZ;
		
	
	if(fp->base == NULL){
		if((fp->base = (char*) malloc(bufsize)) == NULL){
			fp->flag.is_err = 1;
			return EOF;
		}	
	}
	else{
		nc = fp->ptr - fp->base;
		if(write(fp->fd,fp->base,nc)!=nc){
			fp->flag.is_err = 1;
			return EOF;		
		}	
	}

	fp->ptr = fp->base;
	*fp->ptr++ = (char) x;
	fp->cnt = bufsize - 1;
	return x;
}

int fflush(FILE* fp){
	int rc = 0;
	
	if(fp < _iob || fp >= _iob + OPEN_MAX)
		return EOF;
	if(fp->flag.is_write == 1)
		rc = _flushbuf('\0',fp);
	fp->ptr = fp->base;
	fp->cnt = (fp->flag.is_unbuf) ? 1 : BUFSIZ;
	return rc;
}

int fclose(FILE *fp){
	int rc;
	
	if((rc = fflush(fp)) != EOF){
		free(fp->base);
		fp->ptr = NULL;
		fp->cnt = 0;
		fp->base = NULL;
		fp->flag.is_unbuf = 0;
		fp->flag.is_buf = 0;
		fp->flag.is_eof = 0;
		fp->flag.is_err = 0;
	}
	return rc;
}


int main(int argc, char *argv[]) {
    int c;
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
    fclose(&_iob[1]);
}

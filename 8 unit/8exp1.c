#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

void error(char* fmt,...){
	va_list args;
	
	va_start(args,fmt);
	fprintf(stderr,"error: ");
	vfprintf(stderr,fmt,args);
	fprintf(stderr,"\n");
	va_end(args);
	exit(1);
}

void filecopy(int in_fd,int out_fd){
	int n;
	char buf[BUFSIZ];
	
	while((n = read(in_fd,buf,BUFSIZ)) > 0){
		if(write(out_fd,buf,n) !=  n){
			error("write error");		
		}	
	}
}

int main(int argc,char* argv[]){
	int fd;
	
	
	if(argc == 1){
		filecopy(0,1);	
	}
	else{
		while(--argc > 0){
			if((fd = open(*++argv,O_RDONLY)) == -1){
				error("can't  file %s",*argv);			
			}
			else{
				filecopy(fd,1);
				close(fd);
			}	
		}	
	}
}

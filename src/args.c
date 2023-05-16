#include "args.h"
#include "utils.h"

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define DEFAULT_ADDR ((in_addr_t) 0xe0000058)

in_port_t port = 5555;
int is_server = 0;
int set_addr = 0;
struct sockaddr_in mcast_addr;
char upload_file[100];

struct option opts[] = {
    {"port", required_argument, 0, 'p'},
    {"addr", required_argument, 0, 'a'},
    {"server", no_argument, 0, 's'},
    {"file", required_argument, 0, 'f'},
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}
};

char optstr[] = "p:a:q:f:sh";

void display_help(char *arg0) {
    printf("Usage: %s [-s] [-a 224.0.0.88] [-p 5555] [-f FILE]\n", arg0);
    printf(" -s, --server      start as a server\n");
    printf(" -a, --addr IPv4   set address (numbers-and-dots notation)\n");
    printf(" -p, --port NUM    set port\n");
    printf(" -f, --file FILE   upload/save filepath\n");
    printf(" -h, --help        display this message and exit\n");
    exit(EXIT_SUCCESS);
}

int parse_args(int argc, char *argv[]) {
    static char buf[100];
    int c = -1, tmp = 0, err = 0;
    bzero(&mcast_addr, sizeof(mcast_addr));
    while ((c = getopt_long(argc, argv, optstr, opts, NULL)) != -1) {
        switch (c) {
            case 'h': display_help(argv[0]); break;
            case 's': is_server = 1; break;
            case 'p': {
                err = copy_number(&tmp, optarg);
                if (err) return puts("Bad port number!"), -1;
                port = (uint16_t)tmp;
                break;
            }
            case 'a': {
                err = copy_string(buf, optarg);
                if (err || !inet_aton(buf, &mcast_addr.sin_addr)) return puts("Bad address!"), -1;
                set_addr = 1;
                break;
            }
            case 'f': {
                err = copy_string(upload_file, optarg);
                if (err) return puts("Failed when set -f!"), -1;
                break;
            }
            default: return -1;
        }
    }
    if (!set_addr) {
        // default mcast IP: 224.0.0.88
        mcast_addr.sin_addr.s_addr = htonl(DEFAULT_ADDR);
    }
    mcast_addr.sin_port = htons(port);
    mcast_addr.sin_family = AF_INET;
    if (is_server && !upload_file[0]) {
        return fputs("needs -f!", stderr), -1;
    }
    return 0;
}
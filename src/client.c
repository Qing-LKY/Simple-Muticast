#include "args.h"
#include "client.h"
#include "utils.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void client_main() {
    int s, e, loop, n;
    struct sockaddr_in local_addr;
    socklen_t s_len;
    struct ip_mreq mreq;
    char *data;
    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if (s < 0) {
        perror("Create socket");
        exit(EXIT_FAILURE);
    }
    bzero(&local_addr, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = mcast_addr.sin_port;
    e = bind(s, (struct sockaddr *)&local_addr, sizeof(local_addr));
    if (e < 0) {
        perror("Bind address");
        exit(EXIT_FAILURE);
    }
    loop = 1;
    e = setsockopt(s, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop));
    if (e < 0) {
        perror("Set IP_MULTICAST_LOOP");
        exit(EXIT_FAILURE);
    }
    mreq.imr_multiaddr = mcast_addr.sin_addr;
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    e = setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    if (e < 0) {
        perror("Set IP_ADD_MEMBERSHIP");
        exit(EXIT_FAILURE);
    }
    for(;;) {
        s_len = sizeof(local_addr);
        n = recvfrom(s, NULL, 0, MSG_PEEK | MSG_TRUNC, (struct sockaddr *)&local_addr, &s_len);
        if (n < 0) continue;
        data = calloc(1, n + 5);
        n = recvfrom(s, data, n + 5, 0, (struct sockaddr *)&local_addr, &s_len);
        if (n < 0) {
            perror("Receive Msg");
            exit(EXIT_FAILURE);
        }
        printf("Get data: %d Bytes\n", n);
        if (upload_file[0]) {
            e = put_content(upload_file, data, n);
            if (e < 0) exit(EXIT_FAILURE);
        }
        e = write(STDOUT_FILENO, data, n);
        if (e < 0) {
            perror("Standard output");
            exit(EXIT_FAILURE);
        }
        free(data);
        break;
    }
}
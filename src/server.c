#include "args.h"
#include "utils.h"
#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MCAST_INTERVAL 3

void server_main() {
    int s, n, siz;
    char *data;
    s = socket(AF_INET, SOCK_DGRAM, PF_UNSPEC);
    if (s == -1) {
        perror("Create socket");
        exit(EXIT_FAILURE);
    }
    data = get_content(upload_file, &siz);
    if (data == NULL) {
        exit(EXIT_FAILURE);
    }
    for (;;) {
        n = sendto(s, data, siz, 0, (struct sockaddr *)&mcast_addr, sizeof(mcast_addr));
        if (n < 0) {
            perror("Send data");
            exit(EXIT_FAILURE);
        }
        sleep(MCAST_INTERVAL);
    }
}
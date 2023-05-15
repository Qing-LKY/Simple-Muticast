#ifndef ARGS_H
#define ARGS_H

#include <arpa/inet.h>
#include <sys/socket.h>

extern int is_server;
extern struct sockaddr_in mcast_addr;
extern char upload_file[];

int parse_args(int argc, char *argv[]);

#endif
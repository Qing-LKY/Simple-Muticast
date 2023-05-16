#include "args.h"
#include "server.h"
#include "client.h"

#include <stdlib.h>

int main(int argc, char *argv[]) {
    int e;
    e = parse_args(argc, argv);
    if (e < 0) exit(EXIT_FAILURE);
    if (is_server) server_main();
    else client_main();
    return 0;
}
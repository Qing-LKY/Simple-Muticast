#include "args.h"
#include "server.h"

int main(int argc, char *argv[]) {
    int e;
    e = parse_args(argc, argv);
    if (is_server) server_main();
    else {
        
    }
    return 0;
}
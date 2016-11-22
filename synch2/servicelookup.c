#include "helpers.h"
#include <netdb.h>

int main(int argc, char** argv) {
    // Usage: ./servicelookup SERVICE...
    if (argc == 1)
        fprintf(stderr, "Usage: servicelookup NAME [NAME...]\n");

    for (int i = 1; i < argc; ++i) {
        // Look up the corresponding TCP port number
        struct servent* service = getservbyname(argv[i], "tcp");

        // Print it
        int port = service ? ntohs(service->s_port) : 0;
        printf("%s,%d\n", argv[i], port);
    }
}

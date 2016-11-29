#include "helpers.h"
#include <netdb.h>

int main(int argc, char** argv) {
    const char* host = "localhost";
    const char* port = "6168";

    // parse arguments
    int opt;
    while ((opt = getopt(argc, argv, "h:p:")) >= 0) {
        if (opt == 'h')
            host = optarg;
        else if (opt == 'p')
            port = optarg;
    }

    // look up host and port
    struct addrinfo hints, *ai;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;        // use IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // use TCP
    hints.ai_flags = AI_NUMERICSERV;
    int r = getaddrinfo(host, port, &hints, &ai);
    if (r != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
        exit(1);
    }

    // connect to server
    int fd = socket(ai->ai_family, ai->ai_socktype, 0);
    if (fd < 0) {
        perror("socket");
        exit(1);
    }

    r = connect(fd, ai->ai_addr, ai->ai_addrlen);
    if (r < 0) {
        perror("connect");
        exit(1);
    }

    if (optind == argc)
        fprintf(stderr, "Usage: serviceclient NAME [NAME...]\n");

    // write arguments
    FILE* f = fdopen(fd, "a+");
    char buf[BUFSIZ];
    for (; optind < argc; ++optind)
        fprintf(f, "%s\n", argv[optind]);
    // shut down writing (no more arguments)
    fflush(f);
    shutdown(fd, SHUT_WR);
    // read results
    while (fgets(buf, BUFSIZ, f))
        fputs(buf, stdout);

    // done
    fclose(f); // This also closes `fd`.
}

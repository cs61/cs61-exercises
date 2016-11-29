#include "helpers.h"
#include <netdb.h>

int main(int argc, char** argv) {
    const char* host = "localhost";
    const char* port = "6168";
    int max_conns = 10000;
    raise_file_limit();

    int opt;
    while ((opt = getopt(argc, argv, "h:p:n:")) >= 0) {
        if (opt == 'h')
            host = optarg;
        else if (opt == 'p')
            port = optarg;
        else if (opt == 'n')
            max_conns = strtol(optarg, NULL, 0);
    }

    struct addrinfo hints, *ai;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;
    int r = getaddrinfo(host, port, &hints, &ai);
    if (r != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(r));
        exit(1);
    }

    int* cfds = (int*) malloc(max_conns * sizeof(int));
    int nconns;
    double start_time = timestamp();
    for (nconns = 0; nconns < max_conns; ++nconns) {
        cfds[nconns] = socket(ai->ai_family, ai->ai_socktype, 0);
        if (cfds[nconns] < 0) {
            perror("socket");
            break;
        }

        r = connect(cfds[nconns], ai->ai_addr, ai->ai_addrlen);
        if (r < 0) {
            perror("connect");
            break;
        }

        fprintf(stderr, "\r%d/%d connections (%g conns/s)    ",
                nconns, max_conns, nconns / (timestamp() - start_time));
    }

    fprintf(stderr, "\rHolding open %d connections\n", nconns);
    while (1)
        /* do nothing */;
}

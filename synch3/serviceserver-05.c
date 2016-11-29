#include "helpers.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

int make_listen(int port);
void handle_connection(FILE* fin, FILE* fout);
int remove_trailing_whitespace(char* buf);

static int n_connection_threads;

void* connection_thread(void* arg) {
    FILE* f = (FILE*) arg;
    ++n_connection_threads;
    pthread_detach(pthread_self());
    handle_connection(f, f);
    fclose(f);
    --n_connection_threads;
    pthread_exit(0);
}

int main(int argc, char** argv) {
    // Usage: ./serviceserver [PORT]
    int port = 6168;
    if (argc >= 2) {
        port = strtol(argv[1], NULL, 0);
        assert(port > 0 && port <= 65535);
    }

    // Prepare listening socket
    int fd = make_listen(port);

    // Allow many fds
    raise_file_limit();

    while (1) {
        // Accept connection on listening socket
        int cfd = accept(fd, NULL, NULL);
        if (cfd < 0) {
            perror("accept");
            exit(1);
        }

        // If too many threads, wait until one exits
        while (n_connection_threads > 100)
            sched_yield();

        // Start thread to handle connection; no buffering please
        pthread_t t;
        FILE* f = fdopen(cfd, "a+");
        setvbuf(f, NULL, _IONBF, 0);
        int r = pthread_create(&t, NULL, connection_thread, (void*) f);
        if (r != 0) {
            perror("pthread_create");
            exit(1);
        }
    }
}

void handle_connection(FILE* fin, FILE* fout) {
    char buf[BUFSIZ];

    while (fgets(buf, BUFSIZ, fin))
        if (remove_trailing_whitespace(buf)) {
            // Look up the corresponding TCP port number
            struct servent* service = getservbyname(buf, "tcp");

            // Print it
            int port = service ? ntohs(service->s_port) : 0;
            fprintf(fout, "%s,%d\n", buf, port);
        }

    if (ferror(fin))
        perror("read");
}

int make_listen(int port) {
    // Create socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    assert(fd >= 0);

    // Useful options: close-on-exec, reuse-address
    int r = fcntl(fd, F_SETFD, FD_CLOEXEC);
    assert(r >= 0);

    int yes = 1;
    r = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    assert(r >= 0);

    // Bind to port
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = INADDR_ANY;
    r = bind(fd, (struct sockaddr*) &address, sizeof(address));
    assert(r >= 0);

    // Actually start listening
    r = listen(fd, 100);
    assert(r >= 0);

    return fd;
}

int remove_trailing_whitespace(char* buf) {
    int len = strlen(buf);
    while (len > 0 && isspace((unsigned char) buf[len - 1])) {
        --len;
        buf[len] = 0;
    }
    return len;
}

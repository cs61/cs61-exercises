#include "helpers.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

// Connection structure
#define CONN_BUFSIZ 1024
typedef struct conn {
    FILE* f;
    char buf[CONN_BUFSIZ];
    struct conn* next;
    struct conn* prev;
} conn;
#define MAX_CONNS 10240
conn* conns = NULL;

int make_listen(int port);
void handle_connection(conn* c);
int remove_trailing_whitespace(char* buf);

int main(int argc, char** argv) {
    // Usage: ./serviceserver [PORT]
    int port = 6168;
    if (argc >= 2) {
        port = strtol(argv[1], NULL, 0);
        assert(port > 0 && port <= 65535);
    }

    // Prepare listening socket
    int lfd = make_listen(port);
    make_nonblocking(lfd);

    // Prepare connection array
    raise_file_limit();

    while (1) {
        // Prepare set of relevant connections
        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(lfd, &rfds); // New connection attempts
        int max_fd = lfd;
        for (conn* c = conns; c; c = c->next) {
            int fd = fileno(c->f);
            FD_SET(fd, &rfds);
            max_fd = (fd > max_fd ? fd : max_fd);
        }

        // Select to block until we're ready
        (void) select(max_fd + 1, &rfds, NULL, NULL, NULL);

        // Maybe accept an incoming connection
        if (FD_ISSET(lfd, &rfds)) {
            int cfd = accept(lfd, NULL, NULL);
            if (cfd < 0) {
                perror("accept");
                exit(1);
            }
            make_nonblocking(cfd);

            conn* c = (conn*) malloc(sizeof(conn));
            c->f = fdopen(cfd, "a+");
            c->buf[0] = 0; // empty string
            c->next = conns;
            if (conns)
                conns->prev = c;
            c->prev = NULL;
            conns = c;
        }

        // Handle data from existing connections
        for (conn* c = conns; c; ) {
            conn* next = c->next;
            if (FD_ISSET(fileno(c->f), &rfds))
                handle_connection(c); /* might close `c` */
            c = next;
        }
    }
}

void handle_connection(conn* c) {
    size_t len = strlen(c->buf);

    // Attempt to load more data into the buffer.
    // If you fail, maybe try again later
    int ch = EOF;
    while (len != CONN_BUFSIZ - 1
           && (ch = fgetc(c->f)) != EOF
           && ch != '\n') {
        c->buf[len] = ch;
        ++len;
    }
    c->buf[len] = 0;

    // Maybe the user ran out of data to send. Just try again later
    if (len != CONN_BUFSIZ - 1 && ch == EOF
        && ferror(c->f) && errno == EAGAIN)
        return;

    // At this point we have a line

    // Remove trailing whitespace
    if (remove_trailing_whitespace(c->buf)) {
        struct servent* service = getservbyname(c->buf, "tcp");
        int port = service ? ntohs(service->s_port) : 0;
        fprintf(c->f, "%s,%d\n", c->buf, port);
        fflush(c->f);
    }

    c->buf[0] = 0;

    // If the file is done, remove the connection
    if (feof(c->f) || ferror(c->f)) {
        fclose(c->f);
        if (c->prev)
            c->prev->next = c->next;
        else
            conns = c->next;
        if (c->next)
            c->next->prev = c->prev;
        free(c);
    }
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

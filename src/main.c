#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <err.h>
#include "db/njuke_db.h"


static int server_init(unsigned short port)
{
        int ret;
        int sock;
        struct sockaddr_in addr = {0};

        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == -1) {
                perror("socket()");
                goto fail;
        }
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = port;
        ret = bind(sock, (struct sockaddr *) &addr, sizeof(addr));
        if (ret) {
                perror("bind()");
                goto cleanup;
        }
        ret = listen(sock, 5);
        if (ret == -1) {
                perror("listen()");
                goto cleanup;
        }
        return sock;

 cleanup:
        close(sock);
 fail:
        return -1;
}

static void server_run(int sock)
{
        for (;;) {
                int csock;
                struct sockaddr_in addr;
                socklen_t addrlen = sizeof(addr);
                printf("Waiting for client...\n");
                csock = accept(sock, (struct sockaddr *) &addr, &addrlen);
                (void) csock;
                /* TODO: Spin of and handle. */
        }
}

int main(int argc, char **argv)
{
        int sock;
        struct njuke_db *db;

        db = njuke_db_connect(0);
        if (!db)
                err(1, "Could not open database.");
        sock = server_init(7357);
        if (sock == -1)
                err(1, "Could not create server");
        server_run(sock);
        return 0;
}

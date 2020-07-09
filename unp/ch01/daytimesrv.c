#include "unp.h"

#include <time.h>

int main()
{
    int fd, connfd;

    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    time_t ticks;

    fd = Socket(AF_INET, SOCK_STREAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    Bind(fd, (SA *)&servaddr, sizeof(servaddr));
    Listen(fd, LISTENQ);

    for (;;) {
        connfd = Accept(fd, (SA *)NULL, NULL);
        ticks = time(NULL);
        snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buf, strlen(buf));

        Close(connfd);
    }

    return 0;
}
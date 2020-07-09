#include "unp.h"

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvlinep[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 2) {
        err_quit("usage: a.out <IPAddress>");
    } 

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_quit("socket eror");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);

    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
    //if (inet_ntop(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        err_sys("inet_pton error for %s", argv[1]);
    }

    if (connect(sockfd, &servaddr, sizeof(servaddr)) < 0) {
        err_sys("connect error");
    }

    while ((n = read(sockfd, recvlinep, MAXLINE)) > 0) {
        recvlinep[n] = 0;
        if (fputs(recvlinep, stdout) == EOF) {
            err_sys("fputs error");
        }
    }

    if (n < 0) {
        err_sys("read error");
    }


    return 0;
}
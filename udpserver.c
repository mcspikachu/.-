#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>

#define MAX 80
#define PORT 43454
#define SA struct sockaddr

void func(int sockfd) {
    char buff[MAX];
    int n, clen;
    struct sockaddr_in cli;
    clen = sizeof(cli);
    
    for(;;) {
        bzero(buff, MAX);
        recvfrom(sockfd, buff, sizeof(buff), 0, (SA *)&cli, &clen);
        printf("From client: %sTo client: ", buff);

        bzero(buff, MAX);
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        sendto(sockfd, buff, sizeof(buff), 0, (SA *)&cli, clen);

        if (strncmp("exit", buff, 4) == 0) break;
    }
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(sockfd, (SA *)&servaddr, sizeof(servaddr));
    func(sockfd);
    close(sockfd);
}

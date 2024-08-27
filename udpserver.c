#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>  // Required for inet_addr()

#define MAX 80
#define PORT 43454
#define SA struct sockaddr

int main() 
{
    char buff[MAX];
    int n, clen, sockfd;
	struct sockaddr_in servaddr, cli;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Prepare server address
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Bind to localhost (127.0.0.1)
    servaddr.sin_port = htons(PORT);

    // Bind socket to the server address
    bind(sockfd, (SA *)&servaddr, sizeof(servaddr));

    clen = sizeof(cli);
    
    // Start communication
    for(;;) {
        bzero(buff, MAX);
        recvfrom(sockfd, buff, sizeof(buff), 0, (SA *)&cli, &clen);
        printf("From client: %s", buff);
        bzero(buff, MAX);
		printf("\nTo client: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n');
        sendto(sockfd, buff, sizeof(buff), 0, (SA *)&cli, clen);

        if (strncmp("exit", buff, 4) == 0) break;
    }

    // Close the socket
    close(sockfd);
    return 0;
}

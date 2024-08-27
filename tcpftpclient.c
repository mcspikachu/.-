#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    struct sockaddr_in serveraddr;
    int clientsock, n, length;
    char filename[100], filedata[300];

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    clientsock = socket(AF_INET, SOCK_STREAM, 0);
    connect(clientsock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    printf("Enter the name of the file: ");
    scanf("%s", filename);
    length = strlen(filename);
    write(clientsock, filename, length);

    n = read(clientsock, filedata, sizeof(filedata));
    printf("File contents:\n%s", filedata);

    close(clientsock);
    return 0;
}

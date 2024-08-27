#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

int main() {
    struct sockaddr_in serveraddr, clientaddr;
    int serversock, newserversock, clientsize, n, f;
    char filename[100], filedata[300];

    serversock = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(2000);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serversock, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(serversock, 5);

    while (1) {
        clientsize = sizeof(clientaddr);
        newserversock = accept(serversock, (struct sockaddr*)&clientaddr, &clientsize);

        n = read(newserversock, filename, sizeof(filename));
        filename[n] = 0;

        f = open(filename, O_RDONLY);
        n = read(f, filedata, sizeof(filedata));
        close(f);

        write(newserversock, filedata, n);
        close(newserversock);
    }

    close(serversock);
    return 0;
}

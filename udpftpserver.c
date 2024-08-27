#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>

int main() {
    struct sockaddr_in server, client;
    int serversock, fp;
    char filename[20], buffer[100];
    socklen_t clientlen = sizeof(client);

    serversock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(2000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(serversock, (struct sockaddr*)&server, sizeof(server));

    recvfrom(serversock, filename, sizeof(filename), 0, (struct sockaddr*)&client, &clientlen);

    fp = open(filename, O_RDONLY);

    while (1) {
        int bytes_read = read(fp, buffer, sizeof(buffer));
        if (bytes_read == 0)
            break;
        sendto(serversock, buffer, bytes_read, 0, (struct sockaddr*)&client, clientlen);
    }

    strcpy(buffer, "end");
    sendto(serversock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, clientlen);

    close(fp);
    close(serversock);

    return 0;
}

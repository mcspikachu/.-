#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int sock, bytes_received, i = 1;
    char receive[30];
    struct sockaddr_in server_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(17000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(server_addr.sin_zero), 0, 8);

    connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

    while (1) {
        bytes_received = recv(sock, receive, sizeof(receive) - 1, 0);
        receive[bytes_received] = '\0';

        if (strcmp(receive, "exit") == 0) {
            close(sock);
            break;
        } else {
            if (strlen(receive) < 10) {
                printf("Frame %d data %s received\n", i, receive);
                send(sock, receive, strlen(receive), 0);
            } else {
                send(sock, "negative", 9, 0);
            }
            i++;
        }
    }

    return 0;
}

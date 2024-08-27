#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int sock, connected, true = 1, i = 1;
    char send_data[1024], data[1024], fr[30];
    struct sockaddr_in server_addr, client_addr;
    socklen_t sin_size = sizeof(struct sockaddr_in);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(17000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
    listen(sock, 5);

    connected = accept(sock, (struct sockaddr *)&client_addr, &sin_size);

    while (1) {
        printf("Enter Data Frame %d (Enter exit to end): ", i);
        scanf("%s", fr);
        send(connected, fr, strlen(fr), 0);

        if (strcmp(fr, "exit") == 0) {
            break;
        }

        recv(connected, data, sizeof(data), 0);
        if (strlen(data) != 0) {
            printf("Acknowledgement: %s\n", data);
        }
        i++;
    }

    close(sock);
    return 0;
}

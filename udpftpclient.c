#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main() {
    struct sockaddr_in server;
    int s, fp;
    char filename[20], downloaded[20], filedata[100];
    size_t ret;

    s = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(2000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter the name of the file: ");
    scanf("%s", filename);
    printf("Enter a name to save: ");
    scanf("%s", downloaded);

    sendto(s, filename, sizeof(filename), 0, (struct sockaddr*)&server, sizeof(server));

    fp = open(downloaded, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    while (1) {
        recvfrom(s, filedata, sizeof(filedata), 0, NULL, NULL);
        if (strcmp(filedata, "end") == 0)
            break;
        write(fp, filedata, strlen(filedata));
    }

    close(fp);
    close(s);
    printf("File downloaded successfully...\n");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

int errno = 0;

int checkErrno() {
    if (errno == 0) return 0;
    else printf("err: %s (%d)", strerror(errno), errno);
}

void recieve(int sock, void* buffer) {
    recv(sock, buffer, sizeBuffer, 0);
    if (buffer == 0) {
        printf("Connection terminated")
    }
    return buffer;
}

void sendD(int sock, void* buffer, size_t size) {
    size_t sent = 0;
    while (sent < size) {
        ssize_t stat = send(sock, (char*)buffer + sent, size - sent, 0);
        if (stat <= 0) {
            checkErrno();
            return;
        }
        sent += stat;
    }
}

int listenConnect(int listen_port, float *score, int *sender_port) {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t addr_len = sizeof(client_addr);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) return -1;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(listen_port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(server_sock);
        return -1;
    }

    if (listen(server_sock, 1) < 0) {
        close(server_sock);
        return -1;
    }

    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_len);
    if (client_sock < 0) {
        close(server_sock);
        return -1;
    }

    // Receive the first message
    memset(buffer, 0, sizeof(buffer));
    if (recv(client_sock, buffer, sizeof(buffer) - 1, 0) <= 0) {
        close(client_sock);
        close(server_sock);
        return -1;
    }

    sscanf(buffer, "%f %d", score, sender_port);

    // Close the server socket since we're keeping client connection open
    close(server_sock);

    // Return the open client socket
    return client_sock;
}

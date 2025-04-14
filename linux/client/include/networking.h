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

int connect(const char* ip, int port) {
    int sockfd;
    struct sockaddr_in server_addr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Configure server address struct
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported (ipv6 not supported)");
        close(sockfd);
        return -1;
    }

    // Connect to server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sockfd);
        return -1;
    }

    return sockfd;  // Return the connected socket descriptor
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

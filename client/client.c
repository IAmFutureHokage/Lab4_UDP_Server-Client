#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

void close_socket(SOCKET sock) {
#ifdef _WIN32
    shutdown(sock, SD_BOTH);
    closesocket(sock);
    WSACleanup();
#else
    shutdown(sock, SHUT_RDWR);
    close(sock);
#endif
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <domain>\n", argv[0]);
        return -1;
    }

#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return -1;
    }
#endif

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("Cannot open socket!\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(12345);

    char message[100];
    sprintf(message, "getip %s", argv[1]);
    
    if (sendto(sock, message, strlen(message) + 1, 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Error while sending!\n");
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
        return -1;
    }

    char recv_buf[255];
    socklen_t addr_len = sizeof(server_addr);
    int received = recvfrom(sock, recv_buf, sizeof(recv_buf) - 1, 0, (struct sockaddr *)&server_addr, &addr_len);
    if (received == SOCKET_ERROR) {
        printf("Error while receiving!\n");
#ifdef _WIN32
        closesocket(sock);
        WSACleanup();
#else
        close(sock);
#endif
        return -1;
    }

    recv_buf[received] = '\0';
    printf("%s\n", recv_buf);

    close_socket(sock);
    return 0;
}

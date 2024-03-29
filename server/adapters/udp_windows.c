#include "service/udp_server.h"
#include <stdio.h>

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

UDPServer* createUDPServer(int port) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        perror("error WSAStartup");
        return NULL;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSocket == INVALID_SOCKET) {
        perror("error creating socket");
        WSACleanup();
        return NULL;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        perror("error binding socket");
        closesocket(serverSocket);
        WSACleanup();
        return NULL;
    }

    UDPServer* server = (UDPServer*)malloc(sizeof(UDPServer));
    if (!server) {
        perror("error allocating server");
        closesocket(serverSocket);
        WSACleanup();
        return NULL;
    }
    server->socket = serverSocket;
    return server;
}

char* receiveData(UDPServer* server, ClientInfo* client_info) {
    struct sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    int recvLen = recvfrom(server->socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (recvLen == SOCKET_ERROR) {
        perror("error recvfrom");
        return NULL;
    }

    char* data = (char*)malloc(recvLen + 1);
    if (!data) {
        perror("error malloc");
        return NULL;
    }
    strcpy(data, buffer);

    client_info->ip_address = inet_ntoa(clientAddr.sin_addr);
    client_info->port = ntohs(clientAddr.sin_port);

    return data;
}

void sendData(UDPServer* server, const char* data, ClientInfo* client_info) {
    struct sockaddr_in clientAddr;
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr(client_info->ip_address);
    clientAddr.sin_port = htons(client_info->port);

    sendto(server->socket, data, strlen(data), 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
}

void closeUDPServer(UDPServer* server) {
    if (server) {
        closesocket(server->socket);
        free(server);
    }
    WSACleanup();
}

#endif
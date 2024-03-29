#include "../service/udp_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

UDPServer* createUDPServer(int port) {
    int serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (serverSocket < 0) {
        perror("error creating socket");
        return NULL;
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("error binding socket");
        close(serverSocket);
        return NULL;
    }

    UDPServer* server = (UDPServer*)malloc(sizeof(UDPServer));
    if (!server) {
        perror("error allocating server");
        close(serverSocket);
        return NULL;
    }
    server->socket = serverSocket;
    return server;
}

char* receiveData(UDPServer* server, ClientInfo* client_info) {
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    ssize_t recvLen = recvfrom(server->socket, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (recvLen < 0) {
        perror("error receiving data");
        return NULL;
    }

    client_info->ip_address = inet_ntoa(clientAddr.sin_addr);
    client_info->port = ntohs(clientAddr.sin_port);

    char* data = (char*)malloc(recvLen + 1);
    if (!data) {
        perror("error malloc");
        return NULL;
    }
    strcpy(data, buffer);
    return data;
}

void sendData(UDPServer* server, const char* data, ClientInfo* client_info) {
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    memset(&clientAddr, 0, sizeof(clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = inet_addr(client_info->ip_address);
    clientAddr.sin_port = htons(client_info->port);

    sendto(server->socket, data, strlen(data), 0, (struct sockaddr*)&clientAddr, clientAddrLen);
}

void closeUDPServer(UDPServer* server) {
    if (server) {
        close(server->socket);
        free(server);
    }
}

#endif

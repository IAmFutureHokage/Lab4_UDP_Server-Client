#ifndef UDP_SERVER_H
#define UDP_SERVER_H
#include "models/client_info.h"

typedef struct {
    int socket;
} UDPServer;

UDPServer* createUDPServer(int port);

char* receiveData(UDPServer* server, ClientInfo* client_info);

void sendData(UDPServer* server, const char* data, ClientInfo* client_info);

void closeUDPServer(UDPServer* server);

#endif
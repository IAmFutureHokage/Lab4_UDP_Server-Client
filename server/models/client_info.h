#ifndef CLIENT_INFO_H
#define CLIENT_INFO_H

typedef struct {
    char* ip_address;
    int port;
} ClientInfo;

ClientInfo* createClientInfo(const char* ip_address, int port);

void destroyClientInfo(ClientInfo* client_info);

#endif
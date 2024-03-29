#include "client_info.h"
#include <stdlib.h>
#include <string.h>

ClientInfo* createClientInfo(const char* ip_address, int port) {
    ClientInfo* client_info = (ClientInfo*)malloc(sizeof(ClientInfo));
    if (!client_info) {
        return NULL;
    }

    client_info->ip_address = strdup(ip_address);
    if (!client_info->ip_address) {
        free(client_info);
        return NULL;
    }

    client_info->port = port;
    return client_info;
}

void destroyClientInfo(ClientInfo* client_info) {
    if (client_info) {
        free(client_info->ip_address);
        free(client_info);
    }
}
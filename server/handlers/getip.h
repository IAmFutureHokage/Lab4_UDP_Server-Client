#ifndef GETIP_H
#define GETIP_H

#include "service/udp_server.h"
#include "infrastructure/storage.h"
#include "models/domain.h"

void processRequest(UDPServer* server, Storage* storage, const char* request, ClientInfo* client_info);

#endif
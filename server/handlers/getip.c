#include "handlers/getip.h"
#include <stdio.h>
#include <string.h>

void processRequest(UDPServer* server, Storage* storage, const char* request, ClientInfo* client_info) {
    char command[256];
    char domainName[256];

    sscanf(request, "%s %s", command, domainName);

    if (strcmp(command, "getip") == 0) {
        Domain* foundDomain = getDomain(storage, domainName);
        if (foundDomain) {
            char response[256];
            sprintf(response, "%s %s", foundDomain->name, foundDomain->ipAddress);
            printf("Sending response to %s:%d: %s\n", client_info->ip_address, client_info->port, response);
            sendData(server, response, client_info);

            destroyDomain(foundDomain);
        } else {
            printf("Domain not found. Sending response to %s:%d: Domain not found\n", client_info->ip_address, client_info->port);
            sendData(server, "Domain not found", client_info);
        }
    }
}

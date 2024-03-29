#include "infrastructure/storage.h"
#include "models/domain.h"
#include "service/udp_server.h"
#include "handlers/getip.h"
#include "config/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int main() {

    Config* config = loadConfig("config.txt");
    if (!config) {
        fprintf(stderr, "Failed to load configuration.\n");
        return -1;
    }
   
    Storage* storage = createStorage(config->database_path);

   if (!storage) {
        printf("failed to create storage.\n");
        destroyConfig(config);
        return -1;
    }

    UDPServer* server = createUDPServer(config->port);
    if (!server) {
        fprintf(stderr, "error creating UDP-server\n");
        destroyStorage(storage);
        destroyConfig(config);
        return 1;
    }

    printf("UDP server is running. Waiting for requests...\n");

    ClientInfo client_info; 
    bool isRunning = true;
    while (isRunning) {
            clock_t start = clock();
            char* request = receiveData(server, &client_info);
            if (request) {
                printf("Received request from client: %s", request);
                processRequest(server, storage, request, &client_info);
                free(request);
            }
            clock_t end = clock();
            double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        }

    closeUDPServer(server);
    destroyStorage(storage);
    destroyConfig(config);

    return 0;
}

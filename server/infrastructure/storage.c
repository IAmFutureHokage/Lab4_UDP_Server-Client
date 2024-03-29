#include "storage.h"
#include "models/domain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Storage* createStorage(const char* filePath) {
    Storage* storage = (Storage*)malloc(sizeof(Storage));
    if (!storage) {
        return NULL; 
    }
    storage->filePath = strdup(filePath);
    if (!storage->filePath) {
        free(storage);
        return NULL;
    }
    return storage;
}

void destroyStorage(Storage* storage) {
    if (storage) {
        free(storage->filePath);
        free(storage);
    }
}

Domain* getDomain(Storage* storage, const char* name) {
    FILE* file = fopen(storage->filePath, "r");
    if (!file) {
        perror("err opening file");
        return NULL;
    }

    char line[256], domainName[256], ipAddress[256];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s %s", domainName, ipAddress);
        if (strcmp(domainName, name) == 0) {
            Domain* domain = malloc(sizeof(Domain));
            domain->name = strdup(domainName);
            domain->ipAddress = strdup(ipAddress);
            fclose(file);
            return domain;
        }
    }

    fclose(file);
    return NULL;
}

#include "domain.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Domain* createDomain(const char* name, const char* ipAddress) {
    Domain* domain = malloc(sizeof(Domain));
    if (domain) {
        domain->name = strdup(name);
        domain->ipAddress = strdup(ipAddress);
    }
    return domain;
}

void destroyDomain(Domain* domain) {
    if (domain) {
        free(domain->name);
        free(domain->ipAddress);
        free(domain);
    }
}

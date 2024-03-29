#include "domain.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


static int validateDomainName(const char* domainName);
static int validateIpAddress(const char* ipAddress);

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

int validateDomain(const Domain* domain) {
    if (!domain) return 0;
    return validateDomainName(domain->name) && validateIpAddress(domain->ipAddress);
}

static int validateDomainName(const char* domainName) {
    if (!domainName || domainName[0] == '.' || domainName[strlen(domainName) - 1] == '.') {
        return 0;
    }
    int consecutiveDots = 0;
    for (int i = 0; domainName[i]; i++) {
        if (domainName[i] == '.') {
            if (consecutiveDots) return 0;
            consecutiveDots = 1;
        } else {
            consecutiveDots = 0;
            if (!isalnum(domainName[i]) && domainName[i] != '-') {
                return 0;
            }
        }
    }
    return 1;
}

static int validateIpAddress(const char* ipAddress) {
    int num, dots = 0;
    const char *p = ipAddress;

    if (!ipAddress) return 0;
    
    char *token = strtok((char *)ipAddress, ".");
    while (token != NULL) {
        if (!isdigit(*token)) return 0;

        num = atoi(token);
        if (num < 0 || num > 255) return 0; 

        token = strtok(NULL, ".");
        dots++;
    }
    if (dots != 4) return 0;

    return 1;
}
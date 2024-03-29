#ifndef DOMAIN_H
#define DOMAIN_H

typedef struct {
    char* name; 
    char* ipAddress; 
} Domain;

Domain* createDomain(const char* name, const char* ipAddress);
void destroyDomain(Domain* domain);

#endif
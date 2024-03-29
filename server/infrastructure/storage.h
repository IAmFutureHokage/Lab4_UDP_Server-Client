#include "models/domain.h"
#ifndef STORAGE_H
#define STORAGE_H


typedef struct {
    char* filePath;
} Storage;

Storage* createStorage(const char* filePath);
void destroyStorage(Storage* storage);

Domain* getDomain(Storage* storage, const char* name);

#endif

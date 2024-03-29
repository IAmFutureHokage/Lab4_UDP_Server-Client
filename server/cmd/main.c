#include "infrastructure/storage.h"
#include "models/domain.h"
#include <stdio.h>
#include <ctype.h>

int main() {
    char* filePath = "database/data.txt";
    Storage* storage = createStorage(filePath);

    if (!storage) {
        printf("Не удалось создать хранилище.\n");
        return -1;
    }
   
    char* searchName = "reddit.com";
    Domain* foundDomain = getDomain(storage, searchName);
    if (foundDomain) {
        printf("Найден домен: %s %s\n", foundDomain->name, foundDomain->ipAddress);
    } else {
        printf("Домен %s не найден.\n", searchName);
    }

    destroyStorage(storage);

    return 0;
}

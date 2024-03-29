#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Config* loadConfig(const char* config_file) {
    FILE* file = fopen(config_file, "r");
    if (!file) {
        perror("Error opening config file");
        return NULL;
    }

    Config* config = (Config*)malloc(sizeof(Config));
    if (!config) {
        perror("Error allocating memory for config");
        fclose(file);
        return NULL;
    }

    config->port = 12345;
    config->database_path = strdup("database/data.txt");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char key[64], value[256];
        if (sscanf(line, "%63s %255s", key, value) == 2) {
            if (strcmp(key, "port") == 0) {
                config->port = atoi(value);
            }
            if (strcmp(key, "database_path") == 0) {
                free(config->database_path);
                config->database_path = strdup(value);
            }
        }
    }

    fclose(file);
    return config;
}

void destroyConfig(Config* config) {
    if (config) {
        free(config->database_path);
        free(config);
    }
}

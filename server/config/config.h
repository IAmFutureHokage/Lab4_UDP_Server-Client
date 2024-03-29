#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    int port;
    char* database_path;
} Config;

Config* loadConfig(const char* config_file);
void destroyConfig(Config* config);

#endif

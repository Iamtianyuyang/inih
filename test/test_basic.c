#include "ini.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct config_s {
    char host[64];
    int port;
    char app_name[64];
} config_t;

static int handler(void* user, const char* section, const char* name, const char* value)
{
    config_t* config = (config_t*)user;

    printf("parsed: [%s] %s=%s\n", section, name, value);

    if (strcmp(section, "database") == 0 && strcmp(name, "host") == 0) {
        snprintf(config->host, sizeof(config->host), "%s", value);
        return 1;
    }

    if (strcmp(section, "database") == 0 && strcmp(name, "port") == 0) {
        config->port = atoi(value);
        return 1;
    }

    if (strcmp(section, "app") == 0 && strcmp(name, "name") == 0) {
        snprintf(config->app_name, sizeof(config->app_name), "%s", value);
        return 1;
    }

    return 1;
}

int main(void)
{
    config_t config = {{0}, 0, {0}};
    int result = ini_parse(TEST_INI_PATH, handler, &config);

    if (result != 0) {
        fprintf(stderr, "ini_parse failed: %d\n", result);
        return 1;
    }

    if (strcmp(config.host, "127.0.0.1") != 0) {
        fprintf(stderr, "unexpected host: %s\n", config.host);
        return 1;
    }

    if (config.port != 3306) {
        fprintf(stderr, "unexpected port: %d\n", config.port);
        return 1;
    }

    if (strcmp(config.app_name, "ini_parser_demo") != 0) {
        fprintf(stderr, "unexpected app name: %s\n", config.app_name);
        return 1;
    }

    puts("summary:");
    printf("database.host=%s\n", config.host);
    printf("database.port=%d\n", config.port);
    printf("app.name=%s\n", config.app_name);
    puts("ini_parser_test passed");
    return 0;
}

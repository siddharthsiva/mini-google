#include "file_saver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

char* get_cached_result(const char* query) {
    char filename[256];
    snprintf(filename, sizeof(filename), "cache/%s.html", query);
    FILE* f = fopen(filename, "r");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = malloc(size + 1);
    fread(buffer, 1, size, f);
    buffer[size] = '\0';
    fclose(f);
    return buffer;
}

void save_result_to_cache(const char* query, const char* html) {
    mkdir("cache", 0755);
    char filename[256];
    snprintf(filename, sizeof(filename), "cache/%s.html", query);
    FILE* f = fopen(filename, "w");
    if (f) {
        fputs(html, f);
        fclose(f);
    }
}

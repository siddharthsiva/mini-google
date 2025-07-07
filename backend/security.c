#include "security.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

void sanitize_input(char* str) {
    for (char* p = str; *p; ++p) {
        if (*p == '<' || *p == '>' || *p == '"' || *p == '\'' || *p == '.' || *p == '/')
            *p = '_';
    }
}

void log_security_incident(const char* message, const char* detail) {
    mkdir("logs", 0755);
    FILE* f = fopen("logs/security.log", "a");
    if (!f) return;

    time_t now = time(NULL);
    fprintf(f, "[%s] SECURITY ALERT: %s - %s\n", ctime(&now), message, detail);
    fclose(f);
}

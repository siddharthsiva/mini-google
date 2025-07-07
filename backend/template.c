#include "template.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* render_template(const char* file_path, const char* placeholder, const char* content) {
    FILE* f = fopen(file_path, "r");
    if (!f) return strdup("<h1>Template Error</h1>");

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* template = malloc(size + 1);
    fread(template, 1, size, f);
    template[size] = '\0';
    fclose(f);

    char* final = malloc(size + strlen(content) + 1000);
    char* pos = strstr(template, placeholder);
    if (pos) {
        *pos = '\0';
        sprintf(final, "%s%s%s", template, content, pos + strlen(placeholder));
    } else {
        strcpy(final, template);
    }

    free(template);
    return final;
}

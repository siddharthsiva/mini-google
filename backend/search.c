#include "search.h"
#include "file_saver.h"
#include "template.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* process_query(const char* query) {
    char* cached = get_cached_result(query);
    if (cached) return cached;

    char buffer[8192] = "<ul>";

    DIR* dir = opendir("data");
    struct dirent* entry;
    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_REG) {
            char path[256];
            snprintf(path, sizeof(path), "data/%s", entry->d_name);
            FILE* f = fopen(path, "r");
            if (!f) continue;

            char line[256];
            while (fgets(line, sizeof(line), f)) {
                if (strstr(line, query)) {
                    strcat(buffer, "<li>");
                    strcat(buffer, entry->d_name);
                    strcat(buffer, "</li>");
                    break;
                }
            }
            fclose(f);
        }
    }
    closedir(dir);
    strcat(buffer, "</ul>");

    char* html = render_template("html/result_template.html", "{{RESULTS}}", buffer);
    save_result_to_cache(query, html);
    return html;
}

#include "server.h"
#include "search.h"
#include "security.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

void* handle_client(void* arg) {
    int client_fd = *(int*)arg;
    free(arg);

    char buffer[4096] = {0};
    read(client_fd, buffer, sizeof(buffer) - 1);

    if (strstr(buffer, "GET /search?query=")) {
        char query[256] = {0};
        sscanf(strstr(buffer, "query=") + 6, "%[^ ]", query);
        sanitize_input(query);

        if (strstr(query, "rm") || strstr(query, "..")) {
            log_security_incident("Suspicious query attempt", query);
        }

        char* response = process_query(query);
        dprintf(client_fd, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", response);
        free(response);
    } else {
        FILE* f = fopen("html/index.html", "r");
        if (f) {
            char html[8192] = {0};
            fread(html, 1, sizeof(html), f);
            dprintf(client_fd, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n%s", html);
            fclose(f);
        }
    }

    close(client_fd);
    return NULL;
}

void start_server(int port) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 10);

    printf("🌐 Listening on http://localhost:%d\n", port);

    while (1) {
        int* client_fd = malloc(sizeof(int));
        *client_fd = accept(server_fd, NULL, NULL);
        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, client_fd);
        pthread_detach(thread);
    }
}

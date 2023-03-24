#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUF_SIZE 4096
#define SERVER_PORT 8080
#define PATH "./sample_website"
#define NOT_FOUND_HTML "<!doctype html><html><head><h1>404 NOT FOUND</h1></head></html>"

char *get_mime_type(char *name) {
    char *ext = strrchr(name, '.');
    if (!ext) return NULL;
    if(strcmp(ext, ".html") == 0 || strcmp(ext, ".htm") == 0) return "text/html";
    if(strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) return "image/jpeg";
    return NULL;
}
/*int client_socket, char type, int length, char msg */
void send_headers(int client, char *type, int length) {
    char buffer[BUF_SIZE];
    char *mime_type = get_mime_type(type);
    sprintf(buffer, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", mime_type, length);
    send(client, buffer, strlen(buffer), 0);
    printf("%s", buffer);
}

int main() {
    /* Declarations */
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    int server_socket, client_socket, clientaddrlen;
    char buf[BUF_SIZE];
    /* Create socket */
    server_socket = socket(PF_INET, SOCK_STREAM, 0);
    /* Fill in the address structure */
    memset(&serveraddr, 0, sizeof(struct sockaddr_in));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    serveraddr.sin_port = htons(SERVER_PORT);
    /* Bind address to socket */
    bind(server_socket, (struct sockaddr *)&serveraddr, sizeof(struct sockaddr_in));
    /* Activate connect request queue */
    listen(server_socket, SOMAXCONN);
    /* Receive connection */
    clientaddrlen = sizeof(struct sockaddr_in);
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&clientaddr, &clientaddrlen);
        if (client_socket < 0) {
            perror("[-]webserver (accept)");
            continue;
        }
        /* Read data from socket and write it */
        read(client_socket, buf, BUF_SIZE);
        /*Read the request into buf*/
        char reqMethod[BUF_SIZE], reqFile[BUF_SIZE], reqVersion[BUF_SIZE], *data;
        sscanf(buf, "%s %s %s", reqMethod, reqFile, reqVersion);
        /*Print IP and requst info*/
        printf("[%s:%u]\nreqMethod:%s \nreqVersion:%s \nreqFile:%s\t\n", inet_ntoa(clientaddr.sin_addr),
        ntohs(clientaddr.sin_port), reqMethod, reqVersion, reqFile);

        int size;
        char folder_path[BUF_SIZE] = PATH;
        strcat(folder_path, reqFile);
        if(access(folder_path, F_OK) == 0){
            FILE *fp;
            fp = fopen(folder_path, "r");
            if(fp == NULL){
                perror("[-]fp == NULL");
            }
            fseek(fp, 0, SEEK_END);
            size = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            char buffer[BUF_SIZE];
            int bytes_read = 0;
            send_headers(client_socket, reqFile, size);
            while ((bytes_read = fread(buffer, 1, sizeof(buffer), fp))) {
                write(client_socket, buffer, bytes_read);
            }
            fclose(fp);
        }else {
            // char html_404[] = "<!doctype html><html><head><h1>404 NOT FOUND</h1></head></html>";
            send_headers(client_socket, ".html", sizeof(NOT_FOUND_HTML));
            send(client_socket, NOT_FOUND_HTML, sizeof(NOT_FOUND_HTML), 0);
            printf("\n[-] 404 Not found\n");
        }
        /*Close sockets, fp and free memory*/
        close(client_socket);
    }
    close(server_socket);
}
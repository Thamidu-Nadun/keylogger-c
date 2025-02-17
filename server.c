#include <stdio.h>
#include <winsock2.h>
#include "config.h"

#define FULL_FILE_PATH FILE_PATH "\\" FILE_NAME

int main(){
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        printf("Couldn't create the WSA Startup\n");
        return -1;
    }

    struct sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(48421);
    srv.sin_addr.S_un.S_addr = ADDR_ANY;

    SOCKET sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock_fd == SOCKET_ERROR){
        printf("Error: couldn't create the socket\n");
        WSACleanup();
        return -1;
    }

    if (bind(sock_fd, (struct sockaddr*)&srv, sizeof(srv)) == SOCKET_ERROR){
        printf("Error: couldn't bind the socket\n");
        closesocket(sock_fd);
        WSACleanup();
        return -1;
    }

    if (listen(sock_fd, 5) == SOCKET_ERROR){
        printf("Error: couldn't listen\n");
        closesocket(sock_fd);
        WSACleanup();
        return -1;
    }

    printf("Server Listening on port %d\n", ntohs(srv.sin_port));
    while (1){
        SOCKET client = accept(sock_fd, NULL, NULL);
        char buffer[1024];
        FILE *file = fopen(FULL_FILE_PATH, "rb");
        if (!file){
            printf("Could not open file: %s\n", FULL_FILE_PATH);
            closesocket(client);
            continue;
        }
        printf("Sending data on %s\n", FULL_FILE_PATH);
        size_t bytes_read = 0;
        while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0){
            int sent = 0;
            while (sent < bytes_read){
                int n = send(client, buffer+sent, bytes_read-sent, 0);
                if (n == SOCKET_ERROR) break;
                sent += n;
            }
        }
        fclose(file);
        closesocket(client);
    }
    closesocket(sock_fd);
    WSACleanup();
}
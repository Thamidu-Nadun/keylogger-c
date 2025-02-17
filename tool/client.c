#include <stdio.h>
#include <winsock2.h>
#include <getopt.h>

#define FILENAME "out.txt"

int main(int argc, char **argv){
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0){
        printf("WSA Startup Failed\n");
        return -1;
    }

    struct sockaddr_in srv;
    srv.sin_family = AF_INET;

    int port = 0;
    char *ip = NULL;

    if (argc < 3){
        printf("Usage: %s <IP> <PORT>\n", argv[0]);
        return 1;
    }

    int opt;
    while ((opt = getopt(argc, argv, "i:p:")) != -1){
        switch (opt)
        {
        case 'i':
            ip = optarg;
            break;
        case 'p':
            port = atoi(optarg);
            break;
        default:
            break;
        }
    }

    srv.sin_port = htons(port);
    srv.sin_addr.S_un.S_addr = inet_addr(ip);

    printf("Connecting to %s:%d...\n", ip, port);

    SOCKET sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (sock_fd == INVALID_SOCKET){
        printf("Socket creation failed");
        WSACleanup();
        return 1;
    }

    if (connect(sock_fd, (struct sockaddr*)&srv, sizeof(srv)) == SOCKET_ERROR){
        printf("Connection failed %d\n", WSAGetLastError());
        closesocket(sock_fd);
        WSACleanup();
        return 1;
    }

    FILE *file = fopen(FILENAME, "wb");
    if (!file){
        printf("Couldn't open the file");
        closesocket(sock_fd);
        WSACleanup();
        return -1;
    }

    char buffer[1024];
    int bytes_received;
    while ((bytes_received = recv(sock_fd, buffer, sizeof(buffer), 0)) > 0){
        fwrite(buffer, 1, bytes_received, file);
    }

    if (bytes_received == SOCKET_ERROR){
        printf("Received Failed\n");
    }
    closesocket(sock_fd);
    WSACleanup();
    return 0;
}
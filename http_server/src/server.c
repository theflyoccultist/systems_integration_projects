// Socket server implementation

#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
    // Windows
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    // Linux
    #include <unistd.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
#endif

#define PORT 8080

void start_server() {
    SOCKET server_fd, new_socket;                   // file descriptors
    struct sockaddr_in server_addr, client_addr;    // server and client addresses
    int addr_len = sizeof(client_addr);             // address length
    char buffer[1024] = {0};                        // buffer for data
    // response message
    const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nHello from C\n";

    // Create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Config socket
    server_addr.sin_family = AF_INET;           // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;   // localhost
    server_addr.sin_port = htons(PORT);         // port

    // bind socket to port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // listen for connections
    if (listen(server_fd, 10) == SOCKET_ERROR) {
        perror("Listen failed");
        closesocket(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    // accept connection
    while ((new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) != INVALID_SOCKET) {
        int valread = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
        if (valread > 0) {
            buffer[valread] = '\0';
            printf("Recieved: %s\n", buffer);
            send(new_socket, hello, strlen(hello), 0);
            printf("Message sent\n");
        } else {
            printf("No data recieved\n");
        }
        closesocket(new_socket);
    }

    if (new_socket == INVALID_SOCKET) {
        perror("accept failed");
        closesocket(server_fd);
        exit(EXIT_FAILURE);
    }

    closesocket(server_fd);
}
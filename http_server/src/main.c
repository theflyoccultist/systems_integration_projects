// Routing the program to the server

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

#ifdef _WIN32
void init_winsock() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("WSAStartup failed. Error code: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
}
#endif

int main() {
    #ifdef _WIN32
        init_winsock();
    #endif

        start_server();
    
    #ifdef _WIN32
        WSACleanup();
    #endif
        return 0;
}
#include "net.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int get_sock(char* ip, int port) {
    int sock;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket init");
        exit(EXIT_FAILURE);
    }
    
    bzero(&serv_addr, sizeof(serv_addr));

    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);
    serv_addr.sin_family = AF_INET;

    if (connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))) {
        perror("Socket connect");
        exit(EXIT_FAILURE);
    }
    printf("Connected with %s:%d\n", ip, port);

    return sock;
}
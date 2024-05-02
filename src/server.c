#include <winsock2.h>
#include "esocket.h"
#include <stdio.h>

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    struct sockaddr_in localhost;
    esetaddr4(&localhost, NULL, 12345);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    ebind(sock, &localhost);

    char buf[BUFSIZ];
    struct sockaddr_in peer;

    int ret = erecvfrom(sock, buf, BUFSIZ, 0, &peer);
    esendto(sock, buf, ret, 0, &peer);
}

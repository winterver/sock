#include <winsock2.h>
#include "esocket.h"
#include <stdio.h>
#include <io.h>

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    struct sockaddr_in localhost;
    esetaddr4(&localhost, "127.0.0.1", 12345);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    char buf[BUFSIZ];
    struct sockaddr_in peer;

    int ret = read(0, buf, BUFSIZ);
    esendto(sock, buf, ret, 0, &localhost);
    ret = erecvfrom(sock, buf, BUFSIZ, 0, &peer);

    printf("%.*s", ret, buf);
}

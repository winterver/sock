#ifndef _ESOCKET_H_
#define _ESOCKET_H_

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L
    #error "esocket requires C11"
#endif

// supported socket addresses
struct sockaddr_in;
struct sockaddr_in6;
struct sockaddr_un;
struct sockaddr_storage;

// used by accept() & recvfrom(), etc.
static int __esocket_len;

#define esetaddr4(addr, ip, port)                   \
    do {                                            \
        (addr)->sin_family = AF_INET;               \
        (addr)->sin_port = htons(port);             \
        if (ip != NULL)                             \
            (addr)->sin_addr.s_addr = inet_addr(ip);\
        else                                        \
            (addr)->sin_addr.s_addr = INADDR_ANY;   \
    } while(0)

#define ebind(sock, addr)                   \
    _Generic((addr),                        \
        struct sockaddr_in* : bind,         \
        struct sockaddr_in6* : bind,        \
        struct sockaddr_un* : bind,         \
        struct sockaddr_storage* : bind)    \
    (sock, (struct sockaddr*)(addr), sizeof(*(addr)))

#define econnect(sock, addr)                \
    _Generic((addr),                        \
        struct sockaddr_in* : connect,      \
        struct sockaddr_in6* : connect,     \
        struct sockaddr_un* : connect,      \
        struct sockaddr_storage* : connect) \
    (sock, (struct sockaddr*)(addr), sizeof(*(addr)))

#define eaccept(sock, addr)                 \
    _Generic((addr),                        \
        struct sockaddr_in* : accept,       \
        struct sockaddr_in6* : accept,      \
        struct sockaddr_un* : accept,       \
        struct sockaddr_storage* : accept)  \
    (sock, (struct sockaddr*)(addr), (__esocket_len = sizeof(*(addr))) && (addr) != NULL ? &__esocket_len : NULL)

#define esendto(sock, buf, len, flags, addr)    \
    _Generic((addr),                            \
        struct sockaddr_in* : sendto,           \
        struct sockaddr_in6* : sendto,          \
        struct sockaddr_un* : sendto,           \
        struct sockaddr_storage* : sendto)      \
    (sock, buf, len, flags, (struct sockaddr*)(addr), sizeof(*(addr)))

#define erecvfrom(sock, buf, len, flags, addr)  \
    _Generic((addr),                            \
        struct sockaddr_in* : recvfrom,         \
        struct sockaddr_in6* : recvfrom,        \
        struct sockaddr_un* : recvfrom,         \
        struct sockaddr_storage* : recvfrom)    \
    (sock, buf, len, flags, (struct sockaddr*)(addr),  (__esocket_len = sizeof(*(addr))) ? &__esocket_len : NULL)

#endif

#include <winsock2.h>

class socket_base
{
protected:
    socket_base(int type);

public:
    bool is_valid();
    int availible();

protected:
    int sock;
};

class stream_socket : public socket_base
{
public:
    stream_socket();
    int send(const char* buf, int len);
    int recv(char* buf, int len);
};

class dgram_socket : public socket_base
{
public:
    dgram_socket();
    template<class T>
    int sendto(const char* buf, int len, const T& addr);
    template<class T>
    int recvfrom(char* buf, int len, T& addr);
};

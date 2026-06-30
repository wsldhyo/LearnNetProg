#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

class UdpServer {
public:
    UdpServer();
    ~UdpServer();
private:
    void create_sock();
};
#endif // UDP_SERVER_HPP
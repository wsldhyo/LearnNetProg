#include "tcp_server.hpp"
#include "common.hpp"
#include <cstdint>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
TcpServer::TcpServer(uint16_t port) : listen_sock_fd_(-1), port_(port) {}

// TODO
TcpServer::~TcpServer() { close(listen_sock_fd_);}

void TcpServer::start() {
    create_sock();

    bind_listen();

    accept_client();
}

void TcpServer::create_sock() {
  listen_sock_fd_ = socket(PF_INET, SOCK_STREAM, 0);
  if (listen_sock_fd_ == -1) {
    error_handling("failed to create socket\n");
  }
}

void TcpServer::bind_listen() {
  // 填充服务端地址端口，以便绑定socket
  sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(port_);

  if (bind(listen_sock_fd_, (sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    error_handling("failed to bind socket\n");
  }

  if (listen(listen_sock_fd_, 5) == -1) {
    error_handling("listen socket error\n");
  }
}

void TcpServer::accept_client() {
  int32_t clnt_sock{-1};
  sockaddr clnt_addr;
  socklen_t clnt_addr_len = sizeof(clnt_addr);
  for (int32_t i = 0; i < 5; ++i) {
    clnt_sock = accept(listen_sock_fd_, (sockaddr *)&clnt_addr, &clnt_addr_len);
    if (clnt_sock == -1) {
      error_handling("accept peer socket error\n");
    } else {
      std::cout << "connected client" << i + 1 << '\n';
    }
    handle_req(clnt_sock);
    close(clnt_sock);
  }
}

void TcpServer::handle_req(int32_t clnt_sock) {
    std::uint32_t msg_len {0};
    char msg[BUF_SIZE]{};
    while ((msg_len = read(clnt_sock, msg, BUF_SIZE)) != 0) {
      write(clnt_sock, msg, msg_len);
    }
}

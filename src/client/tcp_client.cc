#include "tcp_client.hpp"
#include "common.hpp"
#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

TcpClient::TcpClient(std::string ip, uint16_t port)
    : sock_(-1), ip_(std::move(ip)), port_(port), msg_{0} {
  connect_server();
}

TcpClient::~TcpClient() {
  if (sock_ != -1)
    close(sock_);
}

void TcpClient::connect_server() {
  sock_ = socket(PF_INET, SOCK_STREAM, 0);
  if (sock_ == -1) {

    error_handling("failed to create socket\n");
  }
  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(ip_.c_str());
  addr.sin_port = htons(port_);

  if (connect(sock_, (sockaddr *)&addr, sizeof(addr)) == -1) {
    error_handling("failed to connect server\n");
  } else {
    std::cout << "connect server success\n";
  }
}

void TcpClient::run() {

  while (true) {
    std::cout << "Input message(Q to quit): ";

    fgets(msg_, sizeof(msg_), stdin);

    if (!strcmp(msg_, "q\n") || !strcmp(msg_, "Q\n"))
      break;

    uint32_t send_len = send_msg();
    recv_msg(send_len);
    std::cout << "msg_ from server: " << msg_;
  }
}

int32_t TcpClient::send_msg() { return write(sock_, msg_, strlen(msg_)); }

void TcpClient::recv_msg(uint32_t const send_len) {
  uint32_t recv_len{0};
  int32_t cur_recv_len{0};
  while (recv_len < send_len) {
    cur_recv_len += read(sock_, msg_, sizeof(msg_) - 1);
    if (cur_recv_len == -1) {
      error_handling("read msg from server error!\n");
    }
    recv_len += cur_recv_len;
  }
  msg_[send_len] = '\0';
}
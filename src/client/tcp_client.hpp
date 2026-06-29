#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP
#include "common.hpp"
#include <cstdint>
#include <string>
class TcpClient {
public:
  TcpClient(std::string ip, uint16_t port);
  ~TcpClient();
  void run();

private:
  void connect_server();
  void loop();
  int32_t send_msg();
  void recv_msg(uint32_t const send_len);

private:
  int sock_;
  std::string ip_;
  uint16_t port_;
  char msg_[BUF_SIZE];
};
#endif
#include "common.hpp"
#include <arpa/inet.h>
#include <cstdint>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage:" << argv[0] << "<port>\n";
    exit(1);
  }
  int32_t sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock == -1) {
    error_handling("failed to create socket\n");
  }
  sockaddr_in serv_addr{};
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  if (bind(sock, (sockaddr *)&serv_addr, sizeof(serv_addr) == -1)) {
    error_handling("failed to bind socket");
  }

  sockaddr_in clnt_addr;
  socklen_t clnt_addr_len{0};
  char msg[BUF_SIZE]{};
  ssize_t msg_len{0};
  while (true) {
    clnt_addr_len = sizeof(clnt_addr);
    msg_len = recvfrom(sock, msg, BUF_SIZE, 0, (sockaddr *)&clnt_addr,
                       &clnt_addr_len);
    sendto(sock, msg, msg_len, 0, (sockaddr *)&clnt_addr, clnt_addr_len);
  }
  close(sock);
  return 0;
}
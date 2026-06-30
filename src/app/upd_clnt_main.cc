#include "common.hpp"
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "Usage:" << argv[0] << " <IP> <port>\n";
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

  sockaddr_in from_addr;
  socklen_t from_addr_len{0};
  char msg[BUF_SIZE]{};
  ssize_t msg_len{0};
  while (true) {
    fputs("Input message(q to quit):", stdout);
    fgets(msg, sizeof(msg), stdin);
    if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")) {
      break;
    }
    sendto(sock, msg, BUF_SIZE, 0, (sockaddr *)&serv_addr, sizeof(serv_addr));
    msg_len = recvfrom(sock, msg, BUF_SIZE, 0, (sockaddr *)&from_addr,
                       &from_addr_len);
    msg[msg_len] = '\0';
    std::cout << msg;
  }
  close(sock);
  return 0;
}
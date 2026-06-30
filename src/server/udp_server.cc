#include "udp_server.hpp"
#include "common.hpp"
#include <sys/socket.h>

void UdpServer::create_sock() {
  int serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (serv_sock == -1) {
    error_handling("failed to create sock\n");
  }
}

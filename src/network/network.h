#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>
#include <sys/socket.h>
#include <unistd.h>

#define SOCK_FD int

struct network_config_str {
  uint16_t listen_port;
  union {
    int32_t ipv4;
    int64_t ipv6;
  } addr;
};

SOCK_FD network_config_server(const struct network_config_str *config);
SOCK_FD network_config_multiplexing(SOCK_FD sock_fd,
                                    const uint32_t max_connection);

int network_read_buffer();
int network_write_buffer();

#endif

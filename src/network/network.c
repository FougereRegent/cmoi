#include "network.h"
#include <fcntl.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <unistd.h>

static int set_nonblocking(int socket) {
  int flags = fcntl(socket, F_GETFL, 0);
  if (flags == -1) {
    perror("fcntl(F_GETFL)");
    return -1;
  }

  if (fcntl(socket, F_SETFL, flags | O_NONBLOCK) == -1) {
    perror("fcntl(F_SETFL)");
    return -1;
  }

  return 0;
}

extern int network_config_server(const struct network_config_str *config) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    perror("Cannot create a socket");
    return EXIT_FAILURE;
  }

  int opt = 1;
  if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt)) == -1) {
    perror("setsockopt()");
    return -1;
  }

  struct sockaddr_in address = {
      .sin_addr.s_addr = INADDR_ANY,
      .sin_port = htons(9874),
      .sin_family = AF_INET,
  };
  if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
    perror("bind");
    return -1;
  }

  if (set_nonblocking(socket_fd) == -1)
    return -1;

  if (listen(socket_fd, 8) == -1) {
    perror("listen");
    return -1;
  }

  return socket_fd;
}

extern SOCK_FD network_config_multiplexing(SOCK_FD sock_fd,
                                           const uint32_t max_connection) {
  SOCK_FD epoll_fd = epoll_create1(0);
  struct epoll_event event;

  event.events = EPOLLIN;
  event.data.fd = sock_fd;

  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_fd, &event) == -1) {
    perror("epoll_ctl: socket_fd");
    return EXIT_FAILURE;
  }

  struct epoll_event events[max_connection];

  /*Boucle de parcours des events*/
  while (1) {
    int n_events = epoll_wait(epoll_fd, events, max_connection, -1);
    if (n_events == -1) {
      perror("epoll_wait");
      break;
    }
    for (int i = 0; i < max_connection; ++i) {
      if (events[i].data.fd == sock_fd) {
        // Implements logic to accept

      } else {
        // Implements logic to accept
      }
    }
  }

  return EXIT_SUCCESS;
}

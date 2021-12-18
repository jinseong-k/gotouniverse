#ifndef __TCP_SOCKET_SERVER_HDR_
#define __TCP_SOCKET_SERVER_HDR_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>

typedef struct _SERVER_STRUCT {
  uint32_t idx;
  uint32_t client_addr;
  uint32_t client_port;
  pthread_t sender;
  pthread_t receiver;
  int socket_fd;
} SERVER_STRUCT;

uint32_t create_socket();

#endif  // __TCP_SOCKET_SERVER_HDR_

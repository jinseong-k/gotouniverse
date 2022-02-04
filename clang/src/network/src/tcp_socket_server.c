#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <errno.h>

#include "tcp_socket_server.h"

uint32_t create_socket() {
  int socket_fd = socket(PF_INET, SOCK_STREAM, 0);

  if (socket_fd == 0) {
    fprintf(stderr, "[%s:%d] Fail to create Socket\n",
                    __func__, __LINE__);
    return -1;
  }

  return socket_fd;
}

void *recv_proc(void *_sock) {
  char buf[1024];
  int sock;
  int s;

  sock = *(int *)(_sock);
  while (1) {
    while ( (s = recv(sock, buf, sizeof(buf)-1, 0)) > 0) {
      buf[s] = 0x00;
      fprintf(stderr, "[%s:%d] receive data : [%s]\n",
          __func__, __LINE__, buf);
    }
  }
}

void *send_proc(void *_sock) {
  char buf[1024] = {0, };
  char *data;
  int len;
  int s;
  int sock;

  sock = *(int *)(_sock);

  snprintf(buf, sizeof(buf), "Hello Client");
  len = strlen(buf);
  while (1) {
    while ( len > 0 && (s = send(sock, data, len, 0)) > 0) {
      data += s;
      len -= s;
    }
    sleep(1);
    data = buf;
    len = strlen(buf);
  }
}

void run_proc(void *_server_struct) {
  SERVER_STRUCT *server_struct;
  int thread_join;

  server_struct = (SERVER_STRUCT *)_server_struct;

  pthread_create(&server_struct->sender, NULL, send_proc, (void *)&server_struct->socket_fd);
  pthread_create(&server_struct->receiver, NULL, recv_proc, (void *)&server_struct->socket_fd);
}

int main() {
  int socket_fd, new_socket;
  int ret;
  struct sockaddr_in address;
  int len = sizeof(struct sockaddr);
  int port = 9001;

  int idx = 0;
  SERVER_STRUCT server_struct[16];
  pthread_t worker_thread[16];


  socket_fd = create_socket();
  if (socket_fd < 0) {
    return -1;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  ret = bind(socket_fd, (struct sockaddr *)&address, len);
  if (ret < 0) {
    if (errno == 48) {
      fprintf(stderr, "[%s:%d] Already Used port [%d]\n",
          __func__, __LINE__, port);
    }
    return -1;
  }

  while (1) {
    fprintf(stderr, "[%s:%d]\n", __func__, __LINE__);
    if (idx >= 16) {
      continue;
    }

    if (listen(socket_fd, 16) < 0) {
      fprintf(stderr, "[%s:%d] listen error\n", __func__, __LINE__);
      return -1;
    }

    new_socket = accept(socket_fd, (struct sockaddr *)&address, (socklen_t *)&len);
    fprintf(stderr, "[%s:%d] Connect Client Info [%s:%u]\n",
        __func__, __LINE__, inet_ntoa(address.sin_addr), ntohs(address.sin_port));
    if (new_socket < 0) {
      fprintf(stderr, "[%s:%d] accept error\n", __func__, __LINE__);
      return -1;
    }

    server_struct[idx].client_addr = address.sin_addr.s_addr;
    server_struct[idx].client_port = address.sin_port;
    server_struct[idx].socket_fd = new_socket;
    server_struct[idx].idx = idx;

    run_proc(&server_struct[idx]);
    //pthread_create(&worker_thread[idx], NULL, run_proc, (void *)&server_struct[idx]);

    idx++;
  }

  return 1;
}

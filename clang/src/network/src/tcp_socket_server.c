#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include <pthread.h>

#include <errno.h>

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

int main() {
  int socket_fd, new_socket;
  int ret;
  struct sockaddr_in address;
  int len = sizeof(struct sockaddr);
  int port = 9001;

  pthread_t recv_thread;
  pthread_t send_thread;

  int thread_join;

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

  while(1) {
    if(listen(socket_fd, 16) < 0) {
      fprintf(stderr, "[%s:%d] listen error\n", __func__, __LINE__);
      return -1;
    }

    new_socket = accept(socket_fd, (struct sockaddr *)&address, (socklen_t *)&len);
    if (new_socket < 0) {
      fprintf(stderr, "[%s:%d] accept error\n", __func__, __LINE__);
      return -1;
    }

    pthread_create(&recv_thread, NULL, recv_proc, (void *)&new_socket);
    pthread_create(&send_thread, NULL, send_proc, (void *)&new_socket);

    pthread_join(recv_thread, (void **)&thread_join);
    pthread_join(send_thread, (void **)&thread_join);
  }

}

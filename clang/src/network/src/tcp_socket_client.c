#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>

void *recv_proc(void *_sock) {
  int sock_fd;
  char buf[1024];
  int s;

  sock_fd = *(int *)_sock;

  while (1) {
    while ( (s = recv(sock_fd, buf, sizeof(buf)-1, 0)) > 0) {
      buf[s] = 0x00;
      fprintf(stderr, "[%s:%d] receive data : [%s]\n",
          __func__, __LINE__, buf);
    }
  }
}

void *send_proc(void *_sock) {
  char buffer[1024] = {0, };
  int sock_fd;
  char *data;
  int len;
  int s;

  sock_fd = *(int *)_sock;

  snprintf(buffer, sizeof(buffer), "Hello Server");
  data = buffer;
  len = strlen(buffer);

  s = 0;
  while (1) {
    while (len > 0 && (s = send(sock_fd, data, len, 0)) > 0) {
      data += s;
      len -= s;
    }
    sleep(1);
    data = buffer;
    len = strlen(buffer);
  }
}

int main() {
  struct sockaddr_in server_addr;
  int sock_fd;
  int port = 9001;

  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd <= 0) {
    // TODO Error
    return -1;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
    // TODO Error
    return -1;
  }

  if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    // TODO Error
    return -1;
  }

  pthread_t send_thread;
  pthread_t recv_thread;
  int thread_join;

  pthread_create(&send_thread, NULL, send_proc, (void *)&sock_fd);
  pthread_create(&recv_thread, NULL, recv_proc, (void *)&sock_fd);

  pthread_join(send_thread, (void **)&thread_join);
  pthread_join(recv_thread, (void **)&thread_join);


  return 1;
}

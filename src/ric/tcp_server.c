/* See LICENSE for details */
/* tcp_server: tcp server - task 10, 11, and 12 */

/* HEADERS */
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/* GLOBAL VARIABLES */
extern int errno;

/* FUNCTION DECLARATIONS */
int openSocket(int type, char *func);
void tcpListen(int fd, char *dest, char *port, char *func);

/* FUNCTION DEFINITIONS */
void tcp_server(char *dest, char *port) {
  char *ptr, buffer[BUFSIZ];
  int fd, newfd, ret;
  socklen_t addrlen;
  ssize_t n, nw;
  struct sockaddr_in addr;
  pid_t pid;

  fd = openSocket(SOCK_STREAM, "tcp_server");
  tcpListen(fd, dest, port, "tcp_server");

  while (1) {
    addrlen = sizeof(addr);
    do {
      newfd = accept(fd, (struct sockaddr *)&addr, &addrlen);
    } while (newfd < 0 && errno == EINTR);

    if ((pid = fork()) < 0) {
      fprintf(stderr, "error: tcp_server: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    } else if (!pid) {
      /* CHILD PROCESS */
      close(fd);
      write(STDOUT_FILENO, "echo: ", 6);
      while ((n = read(newfd, buffer, BUFSIZ))) {
        if (n < 0) {
          exit(EXIT_FAILURE);
        }
        ptr = buffer;
        while (n) {
          if ((nw = write(newfd, ptr, n)) < 0) {
            fprintf(stderr, "error: tcp_server: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
          }
          write(STDOUT_FILENO, ptr, nw);
          n -= nw;
          ptr += nw;
        }
      }
      close(newfd);
      exit(EXIT_SUCCESS);
    }
    do {
      ret = close(newfd);
    } while (ret < 0 && errno == EINTR);
    if (ret < 0) {
      fprintf(stderr, "error: tcp_server: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }
}

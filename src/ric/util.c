/* See LICENSE for details */
/* util: util functions for ric, read and writing TCP/UDP messages */

/* HEADERS */
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/* GLOBAL VARIABLES */
extern int errno;

/* FUNCTION DEFINITIONS */
int openSocket(int type, char *func) {
  int fd;
  if ((fd = socket(AF_INET, type, 0)) < 0) {
    fprintf(stderr, "error: %s: %s\n", func, strerror(errno));
    exit(EXIT_FAILURE);
  }
  return fd;
}

void *ngetaddrinfo(int type, int flags, char *dest, char *port, char *func) {
  int errcode;
  struct addrinfo hints, *res;

  memset(&hints, 0, sizeof(hints));
  /* Checking IPv4 only */
  hints.ai_family = AF_INET;
  hints.ai_socktype = type;
  hints.ai_flags = flags;

  if ((errcode = getaddrinfo(dest, port, &hints, &res))) {
    fprintf(stderr, "error: %s: %s\n", func, gai_strerror(errcode));
    exit(EXIT_FAILURE);
  }
  return (void *)res;
}

void tcpConnect(int fd, char *dest, char *port, char *func) {
  int n;
  struct addrinfo *res;

  res = (struct addrinfo *)ngetaddrinfo(SOCK_STREAM, 0, dest, port, func);
  n = connect(fd, res->ai_addr, res->ai_addrlen);
  freeaddrinfo(res);

  if (n < 0) {
    fprintf(stderr, "error: %s: %s\n", func, strerror(errno));
    exit(EXIT_FAILURE);
  }
}

void tcpWrite(int fd, char *msg, int n, char *func) {
  char buffer[BUFSIZ];
  char *ptr = strncpy(buffer, msg, n);
  ssize_t nw;

  while (n) {
    nw = write(fd, ptr, n);
    if (nw < 0) {
      fprintf(stderr, "error: %s: %s\n", func, strerror(errno));
      exit(EXIT_FAILURE);

    } else if (!nw) {
      fprintf(stderr, "error: %s: socket closed\n", func);
      exit(EXIT_FAILURE);
    }
    n -= nw;
    ptr += nw;
  }
}

int tcpRead(int fd, char *buffer, int n, char *func) {
  char *ptr = buffer;
  int nl = n;
  int nr = 0;

  while (nl) {
    nr = read(fd, ptr, nl);
    if (nr < 0) {
      fprintf(stderr, "error: %s: %s\n", func, strerror(errno));
      exit(EXIT_FAILURE);

    } else if (!nr) {
      break;
    }
    nl -= nr;
    ptr += nr;
  }

  return n - nl;
}

void tcpListen(int fd, char *dest, char *port, char *func) {
  struct addrinfo *res;

  res = (struct addrinfo *)ngetaddrinfo(SOCK_STREAM, AI_PASSIVE, dest, port,
                                        func);

  if (bind(fd, res->ai_addr, res->ai_addrlen) < 0) {
    fprintf(stderr, "error: %s: %s\n", func, strerror(errno));
    exit(EXIT_FAILURE);
  }
  freeaddrinfo(res);

  if (listen(fd, 5) < 0) {
    fprintf(stderr, "error: %s: %s\n", func, strerror(errno));
    exit(EXIT_FAILURE);
  }
}

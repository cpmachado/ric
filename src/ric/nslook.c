/* See LICENSE for details */
/* nslook: getaddrinfo - task 2 */

/* HEADERS */
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

/* FUNCTION DEFINITIONS */
void nslook(char *dest) {
  char buffer[INET_ADDRSTRLEN];
  int errcode;
  struct addrinfo hints, *res, *p;
  struct in_addr *addr;

  memset(&hints, 0, sizeof(hints));
  /* Checking IPv4 only */
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_CANONNAME;

  if ((errcode = getaddrinfo(dest, NULL, &hints, &res))) {
    fprintf(stderr, "error: nslook: %s\n", gai_strerror(errcode));
    exit(EXIT_FAILURE);
  }

  printf("canonical hostname: %s\n", res->ai_canonname);

  for (p = res; p; p = p->ai_next) {
    addr = &((struct sockaddr_in *)p->ai_addr)->sin_addr;
    printf("internet address: %s (%08lX)\n",
           inet_ntop(p->ai_family, addr, buffer, sizeof(buffer)),
           (long unsigned int)ntohl(addr->s_addr));
  }
  freeaddrinfo(res);
}

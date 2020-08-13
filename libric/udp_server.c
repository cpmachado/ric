/* See LICENSE for details */
/* udp_server: udp server - task 9 */


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
void
udp_server(char *dest, char *port) {
	char buffer[BUFSIZ];
	char host[NI_MAXHOST], service[NI_MAXSERV];
	int fd, errcode;
	socklen_t addrlen;
	ssize_t n, nread;
	struct addrinfo hints, *res;
	struct sockaddr_in addr;


	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "error: udp_server: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(hints));
	/* Checking IPv4 only */
	hints.ai_family = AF_INET;
	/* UDP */
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;

	if ((errcode = getaddrinfo(dest, port, &hints, &res))) {
		fprintf(stderr, "error: udp_server: %s\n", gai_strerror(errcode));
		exit(EXIT_FAILURE);
	}

	if (bind(fd, res->ai_addr, res->ai_addrlen) < 0) {
		fprintf(stderr, "error: udp_server: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(res);

	while (1) {
		addrlen = sizeof(addr);
		nread = recvfrom(fd, buffer, BUFSIZ, 0,
		                 (struct sockaddr*)&addr, &addrlen);
		if (nread < 0) {
			fprintf(stderr, "error: udp_server: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		write(STDOUT_FILENO, "echo: ", 6);
		write(STDOUT_FILENO, buffer, nread);

		/* Used udp_client code, to reuse code, thus it is extra featured :) */
		errcode = getnameinfo((struct sockaddr*)&addr, addrlen,
		                      host, sizeof(host),
		                      service, sizeof(service), 0);
		if (errcode) {
			fprintf(stderr, "error: udp_server: %s\n", gai_strerror(errcode));
			exit(EXIT_FAILURE);
		}

		printf("sent by [%s:%s]\n", host, service);
		fflush(stdout);

		n = sendto(fd, buffer, nread, 0, (struct sockaddr*)&addr, addrlen);
		if (n < 0) {
			fprintf(stderr, "error: udp_server: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
}


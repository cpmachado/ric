/* See LICENSE for details */
/* udp_client: udp client - task 3, 4, and 5 */


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
udp_client(char *dest, char *port) {
	char *msg = "Hello!\n";
	char buffer[BUFSIZ];
	char host[NI_MAXHOST], service[NI_MAXSERV];
	int fd, errcode;
	socklen_t addrlen;
	ssize_t n;
	struct addrinfo hints, *res;
	struct sockaddr_in addr;


	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "error: udp_client: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(hints));
	/* Checking IPv4 only */
	hints.ai_family = AF_INET;
	/* UDP */
	hints.ai_socktype = SOCK_DGRAM;

	if ((errcode = getaddrinfo(dest, port, &hints, &res))) {
		fprintf(stderr, "error: udp_client: %s\n", gai_strerror(errcode));
		exit(EXIT_FAILURE);
	}

	n = sendto(fd, msg, strlen(msg), 0, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);

	if (n < 0) {
		fprintf(stderr, "error: udp_client: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Task 4 */
	addrlen = sizeof(addr);
	n = recvfrom(fd, buffer, BUFSIZ, 0, (struct sockaddr*)&addr, &addrlen);
	if (n < 0) {
		fprintf(stderr, "error: udp_client: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	write(STDOUT_FILENO, "echo :", 6);
	write(STDOUT_FILENO, buffer, n);
	close(fd);
	errcode = getnameinfo((struct sockaddr*)&addr, addrlen,
	                      host, sizeof(host),
                          service, sizeof(service), 0);
	if (errcode) {
		fprintf(stderr, "error: udp_client: %s\n", gai_strerror(errcode));
		exit(EXIT_FAILURE);
	}

	printf("sent by [%s:%s]\n", host, service);
}


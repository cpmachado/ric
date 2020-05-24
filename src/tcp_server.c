/* See LICENSE for details */
/* tcp_server: tcp server - task 10, 11, and 12 */


/* HEADERS */
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


/* GLOBAL VARIABLES */
extern int errno;


/* FUNCTION DEFINITIONS */
void
tcp_server(char *dest, char *port) {
	char *ptr, buffer[BUFSIZ];
	int fd, newfd, errcode;
	socklen_t addrlen;
	ssize_t n, nw;
	struct addrinfo hints, *res;
	struct sockaddr_in addr;


	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "error: tcp_server: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(hints));
	/* Checking IPv4 only */
	hints.ai_family = AF_INET;
	/* TCP */
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags =  AI_PASSIVE;

	if ((errcode = getaddrinfo(dest, port, &hints, &res))) {
		fprintf(stderr, "error: tcp_server: %s\n", gai_strerror(errcode));
		exit(EXIT_FAILURE);
	}

	if (bind(fd, res->ai_addr, res->ai_addrlen) < 0) {
		fprintf(stderr, "error: tcp_server: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	freeaddrinfo(res);

	if (listen(fd, 5) < 0) {
		fprintf(stderr, "error: tcp_server: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	while (1) {
		addrlen = sizeof(addr);
		if ((newfd = accept(fd, (struct sockaddr*)&addr, &addrlen)) < 0) {
			fprintf(stderr, "error: tcp_server: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		write(STDOUT_FILENO, "echo: ", 6);
		while ((n = read(newfd, buffer, BUFSIZ))) {
			if (n < 0) {
				fprintf(stderr, "error: tcp_server: %s\n", strerror(errno));
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
	}
}


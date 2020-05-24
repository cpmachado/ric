/* See LICENSE for details */
/* tcp_client: tcp client - task 6, 7, and 8 */
/* Task 8 is implemented in ric.c, as it is a signal's treatment procedure */


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
tcp_client(char *dest, char *port) {
	char *msg = "Hello!\n";
	char *ptr, buffer[BUFSIZ];
	int fd, n;
	ssize_t nbytes, nleft, nwritten, nread;
	struct addrinfo hints, *res;


	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "error: tcp_client: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	memset(&hints, 0, sizeof(hints));
	/* Checking IPv4 only */
	hints.ai_family = AF_INET;
	/* TCP */
	hints.ai_socktype = SOCK_STREAM;

	if ((n = getaddrinfo(dest, port, &hints, &res))) {
		fprintf(stderr, "error: tcp_client: %s\n", gai_strerror(n));
		exit(EXIT_FAILURE);
	}

	n = connect(fd, res->ai_addr, res->ai_addrlen);
	freeaddrinfo(res);

	if (n < 0) {
		fprintf(stderr, "error: tcp_client: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	/* Task 7 */
	ptr = strcpy(buffer, msg);
	nbytes = strlen(msg); /* using dynamic message, hence need for length*/

	nleft = nbytes;
	while (nleft) {
		nwritten = write(fd, ptr, nleft);
		if (nwritten < 0) {
			fprintf(stderr, "error: tcp_client: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
			
		} else if (!nwritten) {
			fprintf(stderr, "error: tcp_client: socket closed\n");
			exit(EXIT_FAILURE);
		}
		nleft -= nwritten;
		ptr += nwritten;
	}
	
	nleft = nbytes;
	ptr = buffer;
	while (nleft > 0) {
		nread = read(fd, ptr, BUFSIZ);
		if (nread < 0) {
			fprintf(stderr, "error: tcp_client: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
			
		} else if (!nread) {
			close(fd);
			break;
		}
		nleft -= nread;
		ptr += nread;
	}
	nread = nbytes - nleft;
	close(fd);

	write(STDOUT_FILENO, "echo: ", 6);
	write(STDOUT_FILENO, buffer, nread);
}


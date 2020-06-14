/* See LICENSE for details */
/* tcp_client: tcp client - task 6, 7, and 8 */
/* Task 8 is implemented in ric.c, as it is a signal's treatment procedure */


/* HEADERS */
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


/* FUNCTION DECLARATIONS */
int openSocket(int type, char* func);
void tcpConnect(int fd, char *dest, char *port, char *func);
void tcpWrite(int fd, char *msg, int n, char *func);
int tcpRead(int fd, char *buffer, int n, char *func);


/* FUNCTION DEFINITIONS */
void
tcp_client(char *dest, char *port) {
	char *msg = "Hello!\n";
	char buffer[BUFSIZ];
	int fd;
	int nr;

	fd = openSocket(SOCK_STREAM, "tcp_client");
	tcpConnect(fd, dest, port, "tcp_client");
	tcpWrite(fd, msg, strlen(msg), "tcp_client");
	nr = tcpRead(fd, buffer, strlen(msg), "tcp_client");

	close(fd);
	write(STDOUT_FILENO, "echo: ", 6);
	write(STDOUT_FILENO, buffer, nr);
}


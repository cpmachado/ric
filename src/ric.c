/* See LICENSE for details */
/* ric: RCI Internet command */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

void
usage(void) {
	fprintf(stdout, "ric is a RCI Internet Command.\n");
	fprintf(stdout, "Usage: ric [OPTIONS] [HOSTNAME:PORT]\n");
	fprintf(stdout, "Options:\n");
	fprintf(stdout, "    -h          -- display help and exit\n");
	fprintf(stdout, "    -v          -- display version and exit\n");
	fprintf(stdout, "   - n          -- hostname: Task 1\n");
	fprintf(stdout, "   - w          -- nslookup: Task 2\n");
	fprintf(stdout, "   - u          -- udp_client: Task 3, 4, 5\n");
	fprintf(stdout, "   - t          -- tcp_client: Task 6, 7, 8\n");
	fprintf(stdout, "   - l          -- multiplexes u and t to servers\n");
	fprintf(stdout, "     + u        -- udp_server: Task 9\n");
	fprintf(stdout, "     + t        -- tcp_server: Task 10, 11, 12\n");
	fprintf(stdout, "Default values:\n");
	fprintf(stdout, "  Host: " DEFAULT_DEST "\n");
	fprintf(stdout, "  Port: " DEFAULT_PORT "\n");
}

void
version(void) {
	fprintf(stdout, "ric-" VERSION
	        " Copyright © 2020 "
	        ": Carlos Machado, Mariana Carvalho\n");
}

int
main(int argc, char *argv[]) {
	int c;
	char *dest = NULL, *port = NULL;
	enum {
		NONE,
		HNAME,
		NSLOOK,
		UDP,
		TCP
	} mode = NONE;
	enum {
		CLIENT,
		SERVER
	} type = CLIENT;

	while (--argc > 0 && (*++argv)[0] ==  '-') {
		while ((c = *++argv[0])) {
			switch (c) {
			case 'h': usage(); exit(0);
			case 'v': version(); exit(0);
			case 'n': mode = HNAME; break;
			case 'w': mode = NSLOOK; break;
			case 'u': mode = UDP; break;
			case 't': mode = TCP; break;
			case 'l': type = SERVER; break;
			default:
				usage(); exit(1);
			}
		}
	}

	if (argc > 1) {
		usage();
		exit(1);
	}

	if (argc) {
		if (**argv == ':') {
			port = strtok(*argv, ":");
		} else {
			dest = strtok(*argv, ":");
			port = strtok(NULL, ":");
		}
		if (strtok(NULL, ":")) {
			usage();
			exit(1);
		}
	}

	if (!dest) {
		dest = DEFAULT_DEST;
	}
	if (!port) {
		port = DEFAULT_PORT;
	}

	switch(mode) {
	case HNAME: printf("hostname\n");break;
	case NSLOOK: printf("nslook\n");break;
	case UDP:
		if (type == CLIENT) {
			printf("udp_client\n");
		} else {
			printf("udp_server\n");
		}
		break;
	case TCP:
		if (type == CLIENT) {
			printf("tcp_client\n");
		} else {
			printf("tcp_server\n");
		}
		break;
	default: usage(); exit(1);
	}

	printf("%s:%s\n", dest, port);

	return 0;
}

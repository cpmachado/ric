/* See LICENSE for details */
/* ric: RCI Internet command */


/* HEADERS */
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "ric.h"
#include "util.h"


/* GLOBAL VARIABLES */
extern int errno;


/* FUNCTION DEFINITIONS */
int
main(int argc, char *argv[]) {
	int c;
	char *dest = NULL, *port = NULL;
	int mode = NONE;
	int type = CLIENT;
	int interface = RIC_CLI;

	/* TASK 8 and 12 */
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGPIPE, &act, NULL) < 0) {
		fprintf(stderr, "error: ric: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGCHLD, &act, NULL) < 0) {
		fprintf(stderr, "error: ric: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}


	while (--argc > 0 && (*++argv)[0] ==  '-') {
		while ((c = *++argv[0])) {
			switch (c) {
			case 'h': usage(); exit(EXIT_SUCCESS);
			case 'v': version(); exit(EXIT_SUCCESS);
			case 'n': mode = HNAME; break;
			case 'w': mode = NSLOOK; break;
			case 'u': mode = UDP; break;
			case 't': mode = TCP; break;
			case 'l': type = SERVER; break;
			case 'c': interface = RIC_NCURSES;break;
			default:
				usage();
				exit(EXIT_FAILURE);
			}
		}
	}

	if (argc > 1) {
		usage();
		exit(EXIT_FAILURE);
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
			exit(EXIT_FAILURE);
		}
	}

	if (!dest) {
		dest = DEFAULT_DEST;
	}
	if (!port) {
		port = DEFAULT_PORT;
	}

	switch(mode) {
	case HNAME: hname();break;
	case NSLOOK: nslook(dest);break;
	case UDP:
		if (type == CLIENT) {
			udp_client(dest, port);
		} else {
			udp_server(dest, port);
		}
		break;
	case TCP:
		if (type == CLIENT) {
			tcp_client(dest, port);
		} else {
			tcp_server(dest, port);
		}
		break;
	default:
		usage();
		exit(EXIT_FAILURE);
	}

	(void)interface;
	return EXIT_SUCCESS;
}

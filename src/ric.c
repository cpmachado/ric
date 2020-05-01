/* See LICENSE for details */
/* ric: RCI Internet command */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "ric.h"
#include "util.h"

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
	case HNAME: hname();break;
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

	return 0;
}

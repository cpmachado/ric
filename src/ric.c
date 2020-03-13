/* See LICENSE for details */
/* ric: RCI Internet command */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

void
usage(void) {
	fprintf(stdout, "ric is a RCI Internet command.");
	fprintf(stdout, "Usage: ric [OPTIONS] HOSTNAME:PORT\n");
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

	while (--argc > 0 && (*++argv)[0] ==  '-') {
		while ((c = *++argv[0])) {
			switch (c) {
			case 'h': usage(); exit(0);
			case 'v': version(); exit(0);
			default:
				if (!strcmp("-version", *argv)){
					version();exit(0);
				}
				if (!strcmp("-help", *argv)){
					usage();exit(0);
				}
				usage(); exit(1);
			}
		}
	}
	return 0;
}

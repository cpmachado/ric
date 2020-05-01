/* See LICENSE for details */
/* util: util functions for ric */

#include <stdio.h>

#include "config.h"

void
usage(void) {
	fprintf(stdout,
	        "ric is a RCI Internet Command.\n"
	        "Usage: ric [OPTIONS] [[HOSTNAME]:[PORT]]\n"
	        "Options:\n"
	        "   - h          -- display help and exit\n"
	        "   - v          -- display version and exit\n"
	        "   - n          -- hostname: Task 1\n"
	        "   - w          -- nslookup: Task 2\n"
	        "   - u          -- udp_client: Task 3, 4, 5\n"
	        "   - t          -- tcp_client: Task 6, 7, 8\n"
	        "   - l          -- multiplexes u and t to servers\n"
	        "     + u        -- udp_server: Task 9\n"
	        "     + t        -- tcp_server: Task 10, 11, 12\n"
	        "Default values:\n"
	        "  Host: " DEFAULT_DEST "\n"
	        "  Port: " DEFAULT_PORT "\n");
}

void
version(void) {
	fprintf(stdout,
	        "ric-" VERSION
	        " Copyright © 2020 "
	        ": Carlos Machado, Mariana Carvalho\n");
}

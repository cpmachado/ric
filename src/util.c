/* See LICENSE for details */
/* util: util functions for ric */

/* HEADERS */
#include <stdio.h>

#include "config.h"

#ifndef DEFAULT_DEST
#define DEFAULT_DEST "localhost"
#endif
#ifndef DEFAULT_PORT
#define DEFAULT_PORT "1337"
#endif
#ifndef VERSION
#define VERSION "X.X.X-dev"
#endif

/* FUNCTION DEFINITIONS */
void usage(void) {
  fprintf(stdout, "ric is the RCI Internet Command.\n"
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
                  "   - c          -- ncurses mode\n"
                  "Default values:\n"
                  "  Host: " DEFAULT_DEST "\n"
                  "  Port: " DEFAULT_PORT "\n");
}

void version(void) {
  fprintf(stdout, "ric-" VERSION " Copyright © 2020 "
                  ": Carlos Machado, Mariana Carvalho\n");
}

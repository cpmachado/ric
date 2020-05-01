/* See LICENSE for details */
/* hname: gethostname - task 1 */
/*
 *  Dependency analysis:
 *  - HOST_NAME_MAX: limits.h
 *  - errno: errno.h
 *  - fprintf: stdio.h
 *  - gethostname: unistd.h
 *  - strerror: string.h
 *
 * */


/* HEADERS */
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


/* GLOBAL VARIABLES */
extern int errno;


/* FUNCTION DEFINITIONS */
void
hname(void) {
	/* HOST_NAME_MAX as mentioned in the man page */
	char buffer[HOST_NAME_MAX];

	if (gethostname(buffer, HOST_NAME_MAX)) {
		fprintf(stderr, "error: hname: %s\n", strerror(errno));
	} else {
		fprintf(stderr, "host name: %s\n", buffer);
	}
}


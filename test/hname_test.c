/* See LICENSE for details */
/* hname.test: Testing hname */

/* HEADERS */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ric.h"


/* FUNCTION DEFINITIONS */
int
main(void) {
	char *ptr;

	printf("Testing hname:\n");
	printf("  - calling mhname\n");
	assert((ptr = mhname()));

	free(ptr);
	return 0;
}

/* See LICENSE for details */
/* util: util functions for ric */

/* MACROS */

/* mode macros */
enum {
	NONE,
	HNAME,
	NSLOOK,
	UDP,
	TCP
};

/* type macros */
enum {
	CLIENT,
	SERVER
};

/* interface macros */
enum {
	RIC_CLI,
	RIC_NCURSES
};


/* FUNCTION DECLARATIONS */

/* usage: Print usage information */
void usage(void);

/* version: Print version information */
void version(void);

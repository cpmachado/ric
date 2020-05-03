/* See LICENSE for details */
/* ric: RCI Internet command  header */

/* FUNCTION DECLARATIONS */

/* hname: print hostname, in src/hname.c */
void hname(void);

/* nslook: print ip information of dest, in src/nslook.c */
void nslook(char *dest);

/* udp_client: udp client sends hello to dest:port, in src/udp_client.c */
void udp_client(char *dest, char *port);


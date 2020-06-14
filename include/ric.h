/* See LICENSE for details */
/* ric: RCI Internet command  header */

/* FUNCTION DECLARATIONS */

/* hname: print hostname, in src/ric/hname.c */
void hname(void);

/* nslook: print ip information of dest, in src/ric/nslook.c */
void nslook(char *dest);

/* udp_client: udp client sends hello to dest:port, in src/ric/udp_client.c */
void udp_client(char *dest, char *port);

/* tcp_client: tcp client sends hello to dest:port, in src/ric/tcp_client.c */
void tcp_client(char *dest, char *port);

/* udp_server: udp echo server binds in dest:port, in src/ric/udp_server.c */
void udp_server(char *dest, char *port);

/* tcp_server: tcp echo server binds in dest:port, in src/ric/tcp_server.c */
void tcp_server(char *dest, char *port);


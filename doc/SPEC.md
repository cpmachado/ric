# Specification

This documents defines the specification of ric.

## Functionality

### Task Implementation

It should implement every Task from:

> ---
> Sanguino, J., "A Quick Guide to Networking Software", 5th Edition, Feb 2020
> ---

List of tasks:
- 1. gethostname
- 2. getaddrinfo
- UDP echo Client:
	+ 3. UDP, socket and sendto
	+ 4. UDP and recvfrom
	+ 5. getnameinfo
- TCP echo Client:
	+ 6. TCP, socket and connect
	+ 7. TCP, write and read
	+ 8. TCP and SIGPIPE signal
- UDP echo Server:
	+ 9. UDP server and bind
- TCP echo Server:
	+ 10. TCP server, bind, listen and accept
	+ 11. select
	+ 12. fork

## Design

### Unique command and a library

It should be implemented as a single program, and a library with the
functionality of any given task.

### Modularity

It should be implemented as to be easily extended, with more useful features,
keeping them lean and mean.

Simplicity and Flexibility over a tool with a thousand specific purposes.

It should easily integrate via CLI.


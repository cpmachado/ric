# Architecture

Considering our model, this units shall be redesigned to support it.

List of units, and its description, by category:
* Application(ric):
	- ric.c
		+ Implements CLI, receives arguments, parses, validates and loads any
		  given task.
	- util.c
		+ Implements utility functions for ric, such as usage and version.
* Library(libric):
	- src/ric/hname.c:
		+ Implements gethostname. Task 1
	- src/ric/nslook.c: 
		+ Implements getaddrinfo. Task 2
	- src/ric/udp\_client.c:
		+ Implements udp\_client. Task 3, 4, 5
	- src/ric/tcp\_client.c:
		+ Implements tcp\_client. Task 6, 7, 8
	- src/ric/udp\_server.c:
		+ Implements udp\_server. Task 9
	- src/ric/tcp\_server.c:
		+ Implements tcp\_server. Task 10, 11, 12
